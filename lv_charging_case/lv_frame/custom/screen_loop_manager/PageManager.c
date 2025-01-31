﻿#include "PageManager.h"
#include "custom.h"

struct
{
    // 以下的方向均指目标页面相对与主页的位置，而不是主页运动方向，与主页实际运动方向相反
    // 实际运动方向
    enum PageDir MoveDir;
    // 实际允许运动方向
    uint8_t State;
    // 允许运动方向
    uint8_t Dir;
    // 管理器主体
    lv_obj_t* obj;
    // 管理器背景层
    lv_obj_t* BackGround;
    // 默认管理器样式
    lv_style_t DefaultStyle;
    // 永远指向无触摸时显示的页面
    PageTypeHandle* HomePage;
    // 动画结构体
    lv_anim_t Anim;
    int32_t xStart;
    int32_t yStart;
    int32_t pos_x;
    int32_t pos_y;
    int32_t LimitSize;
}PageManager;

// 配置自定义回调
struct PM_Custom_Fun PM_Custom_Cb = {
	.status_bar_bottom_update = lv_upadate_status_bar_bottom_by_id,
	.status_bar_top_update = NULL,
    .ble_setting_cmd_send = custom_client_send_ble_setting,
};

#if EnergyTrigger
struct EnergyParam PM_Energy_Trig = {
    .LastTick = 0,
    .ReleasedFlag = 0,
};

u32 PM_Update_LastTick()
{
    PM_Energy_Trig.LastTick = lv_tick_get();
}

u32 PM_Get_LastTick()
{
    return PM_Energy_Trig.LastTick;
}

void PM_Set_ReleasedFlag(u8 flag)
{
    PM_Energy_Trig.ReleasedFlag = flag;
}

u8 PM_Get_ReleasedFlag()
{
    return PM_Energy_Trig.ReleasedFlag;
}

#endif

static PageTypeHandle* GetDirPage(PageTypeHandle* Page, enum PageDir Dir)
{
    PageTypeHandle* Pagebuf;
    switch(Dir)
    {
        case PageNone:{
            Pagebuf = Page;
        }break;

        case PageUp:{
            Pagebuf = Page->Up.Page;
        }break;

        case PageDown:{
            Pagebuf = Page->Down.Page;
        }break;

        case PageLeft:{
            Pagebuf = Page->Left.Page;
        }break;

        case PageRight:{
            Pagebuf = Page->Right.Page;
        }break;

        default:{
        }break;
    }
    if(Pagebuf == NULL)
    {
        DEBUG("GetDirPage Failed [%d]\r\n", Dir);
        return NULL;
    }
    return Pagebuf;
}

static void SetDirPage(PageTypeHandle* SourcePage, enum PageDir Dir, PageTypeHandle* TargetPage)
{
    if(TargetPage == NULL)
    {
        DEBUG("SetDirPage Failed TargetPage Is NULL\r\n");
        return;
    }

    switch(Dir)
    {
        case PageNone:{
            DEBUG("Cannot Set Self DirPage\r\n");
        }break;

        case PageUp:{
            SourcePage->Up.Page = TargetPage;
        }break;

        case PageDown:{
            SourcePage->Down.Page = TargetPage;
        }break;

        case PageLeft:{
            SourcePage->Left.Page = TargetPage;
        }break;

        case PageRight:{
            SourcePage->Right.Page = TargetPage;
        }break;

        default:{
        }break;
    }
}

static lv_obj_t* GetDirObj(PageTypeHandle* Page, enum PageDir Dir)
{
    PageTypeHandle* Pagebuf = GetDirPage(Page, Dir);
    if(Pagebuf == NULL)
    {
        DEBUG("GetDirObj Failed DirPage[%d] Is Null\r\n", Dir);
        return NULL;
    }
    return Pagebuf->obj;
}

static uint8_t GetDirState(PageTypeHandle* Page, enum PageDir Dir)
{
    PageTypeHandle* Pagebuf = GetDirPage(Page, Dir);
    if(Pagebuf == NULL)
    {
        DEBUG("GetDirState Failed DirPage[%d] Is Null\r\n", Dir);
        return INVAILD;
    }
    return Pagebuf->State;
}

static uint8_t GetDirMode(PageTypeHandle* Page, enum PageDir Dir)
{
    enum MoveMode Mode;
    switch(Dir)
    {
        case PageNone:{
            Mode = LOAD_ANIM_NONE;
        }break;

        case PageUp:{
            Mode = Page->Up.Mode;
        }break;

        case PageDown:{
            Mode = Page->Down.Mode;
        }break;

        case PageLeft:{
            Mode = Page->Left.Mode;
        }break;

        case PageRight:{
            Mode = Page->Right.Mode;
        }break;

        default:{
        }break;
    }
    return Mode;
}

static void SetDirMode(PageTypeHandle* Page, enum PageDir Dir, enum MoveMode Mode)
{
    switch(Dir)
    {
        case PageNone:{
            DEBUG("Cannot Set Slef DirMode\r\n");
        }break;

        case PageUp:{
            Page->Up.Mode = Mode;
        }break;

        case PageDown:{
            Page->Down.Mode = Mode;
        }break;

        case PageLeft:{
            Page->Left.Mode = Mode;
        }break;

        case PageRight:{
            Page->Right.Mode = Mode;
        }break;

        default:{
        }break;
    }
}

static void PageMoveDistance(enum PageDir Dir, lv_coord_t Distance)
{
    PageTypeHandle* SourcePage = PageManager.HomePage;
    PageTypeHandle* TargetPage = GetDirPage(PageManager.HomePage, Dir);

    // 发送坐标变化事件
    lv_area_t src_ori;
    lv_obj_get_coords(SourcePage->obj, &src_ori);
    lv_event_send(SourcePage->obj, LV_EVENT_SIZE_CHANGED, &src_ori);

    lv_area_t tar_ori;
    lv_obj_get_coords(TargetPage->obj, &tar_ori);
    lv_event_send(TargetPage->obj, LV_EVENT_SIZE_CHANGED, &tar_ori);

    if(TargetPage == SourcePage)
    {
        if(Distance == 0)
        {
            // 直接复位画面
            DEBUG("HomePage Reset\r\n");
            lv_obj_set_pos(SourcePage->obj, 0, 0);
            // 以下代码以防万一
            // if(PageManager.Dir & LV_DIR_HOR)
            // {
            //     if(PageManager.Dir & LV_DIR_LEFT)
            //     {
            //         lv_obj_align_to(SourcePage->Left.Page->obj, SourcePage->obj, LV_ALIGN_CENTER, lv_obj_get_width(SourcePage->obj), 0);
            //     }
            //     if(PageManager.Dir & LV_DIR_RIGHT)
            //     {
            //         lv_obj_align_to(SourcePage->Right.Page->obj, SourcePage->obj, LV_ALIGN_CENTER, -lv_obj_get_width(SourcePage->obj), 0);
            //     }
            // }else{
            //     if(PageManager.Dir & LV_DIR_TOP)
            //     {
            //         lv_obj_align_to(SourcePage->Up.Page->obj, SourcePage->obj, LV_ALIGN_CENTER, 0, -lv_obj_get_height(SourcePage->obj));
            //     }
            //     if(PageManager.Dir & LV_DIR_BOTTOM)
            //     {
            //         lv_obj_align_to(SourcePage->Down.Page->obj, SourcePage->obj, LV_ALIGN_CENTER, 0, lv_obj_get_height(SourcePage->obj));
            //     }
            // }
        }else{
            DEBUG("PageMoveDistance Failed Cannot Move Self\r\n");
        }
        return;
    }

    switch(GetDirMode(SourcePage, Dir))
    {
        case LOAD_ANIM_NONE:{
            DEBUG("PageMoveDistance Failed Not Allow No Anim To Move Page\r\n");
        }break;

        case LOAD_ANIM_MOVE:{
            switch(Dir)
            {
                case PageUp:{
                    lv_obj_set_pos(SourcePage->obj, 0, Distance);
                    lv_obj_align_to(TargetPage->obj, SourcePage->obj, LV_ALIGN_CENTER, 0, -lv_obj_get_height(SourcePage->obj));
                }break;

                case PageDown:{
                    lv_obj_set_pos(SourcePage->obj, 0, Distance);
                    lv_obj_align_to(TargetPage->obj, SourcePage->obj, LV_ALIGN_CENTER, 0, lv_obj_get_height(SourcePage->obj));
                }break;

                case PageLeft:{
                    lv_obj_set_pos(SourcePage->obj, Distance, 0);
                    lv_obj_align_to(TargetPage->obj, SourcePage->obj, LV_ALIGN_CENTER, -lv_obj_get_width(SourcePage->obj), 0);
                }break;

                case PageRight:{
                    lv_obj_set_pos(SourcePage->obj, Distance, 0);
                    lv_obj_align_to(TargetPage->obj, SourcePage->obj, LV_ALIGN_CENTER, lv_obj_get_width(SourcePage->obj), 0);
                }break;

                default:{
                }break;
            }
        }break;

        case LOAD_ANIM_OVER:{
            switch(Dir)
            {
                case PageUp:{
                    lv_obj_set_pos(TargetPage->obj, 0, Distance - lv_obj_get_height(TargetPage->obj));
                }break;

                case PageDown:{
                    lv_obj_set_pos(TargetPage->obj, 0, Distance + lv_obj_get_height(TargetPage->obj));
                }break;

                case PageLeft:{
                    lv_obj_set_pos(TargetPage->obj, Distance - lv_obj_get_width(TargetPage->obj), 0);
                }break;

                case PageRight:{
                    lv_obj_set_pos(TargetPage->obj, Distance + lv_obj_get_width(TargetPage->obj), 0);
                }break;

                default:{
                }break;
            }
        }break;

        case LOAD_ANIM_LEAVE:{
            switch(Dir)
            {
                case PageUp:{
                    lv_obj_set_pos(SourcePage->obj, 0, Distance);
                }break;

                case PageDown:{
                    lv_obj_set_pos(SourcePage->obj, 0, Distance);
                }break;

                case PageLeft:{
                    lv_obj_set_pos(SourcePage->obj, Distance, 0);
                }break;

                case PageRight:{
                    lv_obj_set_pos(SourcePage->obj, Distance, 0);
                }break;

                default:{
                }break;
            }
        }break;

        case LOAD_ANIM_ROTATE:{
        }break;

        default:{
        }break;
    }
}

static void Anim_cb(void * var, int32_t Value)
{
    PageMoveDistance(PageManager.MoveDir, Value);
}

static void AnimReady_cb(lv_anim_t * Anim)
{
    DEBUG("Anim Is Run Over\r\n");
    lv_anim_set_repeat_delay(&PageManager.Anim, 0xff);
    if(Anim->repeat_delay)
    {
        PM_SetHomePage(GetDirPage(PageManager.HomePage, Anim->repeat_delay));
    }
    PageMoveDistance(PageNone, 0);
    printf("id = %d", PageManager.HomePage->id);
    PM_Custom_Cb.status_bar_bottom_update(PageManager.HomePage->id); // 动画结束回调，根据id去更新底部进度条

    // 进入音量页面，需要蓝牙进入no lantacy模式，加快响应
    static u8 no_lantacy_state = 0;
    if(PageManager.HomePage->id == ID_SCREEN_VOLUME) {
        if(no_lantacy_state == 0) {
            no_lantacy_state = 1;
            PM_Custom_Cb.ble_setting_cmd_send(CMD_BLE_NO_LANTACY_ON);
        }
        
    } else {
        if(no_lantacy_state == 1) {
            no_lantacy_state = 0;
            PM_Custom_Cb.ble_setting_cmd_send(CMD_BLE_NO_LANTACY_OFF);
        }
    }

    PageManager.MoveDir = PageNone;
    PageManager.pos_x   = 0;
    PageManager.pos_y   = 0;
}

static void AnimToPage(enum PageDir Dir, lv_coord_t Distance)
{
    lv_coord_t Start = Distance, End = 0;
    switch(Dir)
    {
        case PageNone:{
            End = 0;
        }break;

        case PageUp:{
            End = lv_obj_get_height(PageManager.HomePage->obj);
        }break;

        case PageDown:{
            End = -lv_obj_get_height(PageManager.HomePage->obj);
        }break;

        case PageLeft:{
            End = lv_obj_get_width(PageManager.HomePage->obj);
        }break;

        case PageRight:{
            End = -lv_obj_get_width(PageManager.HomePage->obj);
        }break;

        default:{
        }break;
    }
    lv_anim_set_repeat_delay(&PageManager.Anim, Dir);
    lv_anim_set_values(&PageManager.Anim, Start, End);
    lv_anim_set_time(&PageManager.Anim, lv_anim_speed_to_time(AnimMoveSpeed, Start, End));
    lv_anim_set_path_cb(&PageManager.Anim, AnimMoveMode);
    lv_anim_set_exec_cb(&PageManager.Anim, Anim_cb);
    lv_anim_set_ready_cb(&PageManager.Anim, AnimReady_cb);
    lv_anim_start(&PageManager.Anim);
}

static void dragend_event_handler(lv_event_t * event)
{
    lv_coord_t act_x = 0, act_y = 0;
    // 已被占用的面积
    int ResidueSize = 0;
    switch(GetDirMode(PageManager.HomePage, PageManager.MoveDir))
    {
        case LOAD_ANIM_NONE:{
            act_x = lv_obj_get_x(PageManager.HomePage->obj);
            act_y = lv_obj_get_y(PageManager.HomePage->obj);
        }break;

        case LOAD_ANIM_MOVE:{
            act_x = lv_obj_get_x(PageManager.HomePage->obj);
            act_y = lv_obj_get_y(PageManager.HomePage->obj);
            ResidueSize += LV_ABS((act_x + 1) * lv_obj_get_height(PageManager.HomePage->obj));
            if(ResidueSize == 0)
            {
                ResidueSize += LV_ABS((act_y + 1) * lv_obj_get_width(PageManager.HomePage->obj));
            }
        }break;

        case LOAD_ANIM_OVER:{
            act_x = lv_obj_get_x(GetDirObj(PageManager.HomePage, PageManager.MoveDir));
            act_y = lv_obj_get_y(GetDirObj(PageManager.HomePage, PageManager.MoveDir));

            // 转换成覆盖页面移动距离
            switch(PageManager.MoveDir) 
            {
                case PageUp:{
                    act_y += HEIGHT;
                    ResidueSize += LV_ABS((act_y + 1) * lv_obj_get_width(PageManager.HomePage->obj));
                }break;
                case PageDown:{
                    act_y -= HEIGHT;
                    ResidueSize += LV_ABS((act_y + 1) * lv_obj_get_width(PageManager.HomePage->obj));
                }break;
                case PageLeft:{
                    act_x += WIDTH;
                    ResidueSize += LV_ABS((act_x + 1) * lv_obj_get_height(PageManager.HomePage->obj));
                }break;
                case PageRight:{
                    act_x -= WIDTH;
                    ResidueSize += LV_ABS((act_x + 1) * lv_obj_get_height(PageManager.HomePage->obj));
                }break;
            }

        }break;

        case LOAD_ANIM_LEAVE:{
            act_x = lv_obj_get_x(PageManager.HomePage->obj);
            act_y = lv_obj_get_y(PageManager.HomePage->obj);
               switch(PageManager.MoveDir) 
            {
                case PageUp:
                case PageDown:{
                    ResidueSize += LV_ABS((act_y + 1) * lv_obj_get_width(PageManager.HomePage->obj));
                }break;
                case PageLeft:
                case PageRight:{
                    ResidueSize += LV_ABS((act_x + 1) * lv_obj_get_height(PageManager.HomePage->obj));
                }break;
            }
        }break;

        case LOAD_ANIM_ROTATE:{
        }break;

        default:{
        }break;
    }
    
    DEBUG("LV_EVENT_RELEASED[%d] [%d] [%d] [%d]!!!\r\n", act_x, act_y, PageManager.MoveDir, ResidueSize);
    DEBUG("pos_x[%d], pos_y[%d]\r\n", PageManager.pos_x, PageManager.pos_y);

#if EnergyTrigger
    PM_Set_ReleasedFlag(1);
    b_printf("lasttick: %d", PM_Get_LastTick());
    u32 elaps = lv_tick_elaps(PM_Get_LastTick());
    b_printf("elap: %d", elaps);
    if(ResidueSize > PageManager.LimitSize || elaps < EnergyTime)
#else
    if(ResidueSize > PageManager.LimitSize)
#endif
    {
        DEBUG("MovePage [%d]\r\n",  PageManager.MoveDir);
        AnimToPage(PageManager.MoveDir, act_y + act_x);
    }else{
        AnimToPage(PageNone, act_y + act_x);
    }
    PageManager.State = LV_DIR_NONE;
}

static void draging_event_handler(lv_event_t * event)
{
#if EnergyTrigger
    if(PM_Get_ReleasedFlag() == 1)
    {
        PM_Update_LastTick();
        PM_Set_ReleasedFlag(0);
    }
#endif

    if(PageManager.Dir == LV_DIR_NONE)
    {
        DEBUG("No Page Can Move\r\n");
        lv_obj_remove_event_cb(PageManager.obj, draging_event_handler);
        lv_obj_remove_event_cb(PageManager.obj, dragend_event_handler);
        return;
    }

    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL)  return;

    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);
    if(LV_ABS(vect.x) == LV_ABS(vect.y))
    {
        return;
    }

    if(PageManager.State == LV_DIR_NONE)
    {
        // 打断动画
        if(lv_anim_del(&PageManager, Anim_cb))
        {
            DEBUG("Anim Is Del\r\n");
        }
        PageManager.MoveDir = PageNone;
        PageManager.pos_x   = 0;
        PageManager.pos_y   = 0;
        PageManager.xStart = lv_obj_get_x(PageManager.HomePage->obj);
        PageManager.yStart = lv_obj_get_y(PageManager.HomePage->obj);
        if(LV_ABS(vect.x) > LV_ABS(vect.y))
        {
            // 横向优先
            if(PageManager.Dir & LV_DIR_HOR)
            {
                // 允许横向运动
                PageManager.State |= (PageManager.Dir & LV_DIR_HOR);
            }else{
                PageManager.State |= (PageManager.Dir & LV_DIR_VER);
            }
        }else{
            // 纵向优先
            if(PageManager.Dir & LV_DIR_VER)
            {
                // 允许纵向运动
                PageManager.State |= (PageManager.Dir & LV_DIR_VER);
            }else{
                PageManager.State |= (PageManager.Dir & LV_DIR_HOR);
            }
        }
    }

    // if(PageManager.State == LV_DIR_NONE)
    // {
    //     // 打断动画
    //     if(PageManager.Anim.repeat_delay != 0xff)
    //     {
    //         lv_anim_del(&PageManager, Anim_cb);
    //         DEBUG("Anim Is Del [%d]\r\n", PageManager.MoveDir);
    //     }else{
    //         DEBUG("First Touch [%d]\r\n", PageManager.MoveDir);
    //     }

    //     if(PageManager.MoveDir == PageNone)
    //     {
    //         if(LV_ABS(vect.x) > LV_ABS(vect.y))
    //         {
    //             // 横向优先
    //             if(PageManager.Dir & LV_DIR_HOR)
    //             {
    //                 // 允许横向运动
    //                 PageManager.State |= (PageManager.Dir & LV_DIR_HOR);
    //             }else{
    //                 PageManager.State |= (PageManager.Dir & LV_DIR_VER);
    //             }
    //         }else{
    //             // 纵向优先
    //             if(PageManager.Dir & LV_DIR_VER)
    //             {
    //                 // 允许纵向运动
    //                 PageManager.State |= (PageManager.Dir & LV_DIR_VER);
    //             }else{
    //                 PageManager.State |= (PageManager.Dir & LV_DIR_HOR);
    //             }
    //         }
    //     }else{
    //         if(PageManager.MoveDir & LV_DIR_HOR)
    //         {
    //             PageManager.State |= (PageManager.Dir & LV_DIR_HOR);
    //         }else{
    //             PageManager.State |= (PageManager.Dir & LV_DIR_VER);
    //         }
    //     }

    //     PageManager.pos_x   = 0;
    //     PageManager.pos_y   = 0;
    //     PageManager.xStart = lv_obj_get_x(PageManager.HomePage->obj);
    //     PageManager.yStart = lv_obj_get_y(PageManager.HomePage->obj);

    //     DEBUG("PageManager.State [0x%02x] [0x%02x]\r\n", PageManager.State, PageManager.Dir);
    // }

    PageManager.pos_x += vect.x;
    PageManager.pos_y += vect.y;

    lv_coord_t xBuf = PageManager.pos_x + PageManager.xStart;
    lv_coord_t yBuf = PageManager.pos_y + PageManager.yStart;

    if (xBuf > WIDTH) {
        xBuf = WIDTH;
    } else if (xBuf < -WIDTH) {
        xBuf = -WIDTH;
    }

    if (yBuf > HEIGHT) {
        yBuf = HEIGHT;
    } else if (yBuf < -HEIGHT) {
        yBuf = -HEIGHT;
    }


    switch(PageManager.State)
    {
        case LV_DIR_LEFT:{
            // DEBUG("LV_DIR_LEFT [%d]\r\n", xBuf);
            if(xBuf > 0)
            {
                PageManager.MoveDir = PageLeft;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }else{
                if(PageManager.MoveDir == PageLeft)
                {
                    PageMoveDistance(PageManager.MoveDir, 0);
                }
                PageManager.MoveDir = PageNone;
            }
        }break;

        case LV_DIR_RIGHT:{
            // DEBUG("LV_DIR_RIGHT [%d]\r\n", xBuf);
            if(xBuf < 0)
            {
                PageManager.MoveDir = PageRight;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }else{
                if(PageManager.MoveDir == PageRight)
                {
                    PageMoveDistance(PageManager.MoveDir, 0);
                }
                PageManager.MoveDir = PageNone;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }
        }break;

        case LV_DIR_TOP:{
            // DEBUG("LV_DIR_TOP [%d]\r\n", PageManager.pos_y);
            if(yBuf > 0)
            {
                PageManager.MoveDir = PageUp;
                PageMoveDistance(PageManager.MoveDir, yBuf);
            }else{
                if(PageManager.MoveDir == PageUp)
                {
                    PageMoveDistance(PageManager.MoveDir, 0);
                }
                PageManager.MoveDir = PageNone;
            }
        }break;

        case LV_DIR_BOTTOM:{
            // DEBUG("LV_DIR_BOTTOM [%d]\r\n", PageManager.pos_y);
            if(yBuf < 0)
            {
                PageManager.MoveDir = PageDown;
                PageMoveDistance(PageManager.MoveDir, yBuf);
            }else{
                if(PageManager.MoveDir == PageDown)
                {
                    PageMoveDistance(PageManager.MoveDir, 0);
                }
                PageManager.MoveDir = PageNone;
            }
        }break;

        case LV_DIR_HOR:{
            // DEBUG("LV_DIR_HOR [%d] [%d]\r\n", xBuf, PageManager.MoveDir);
            if(xBuf > 0)
            {
                if(PageManager.MoveDir == PageRight)
                {
                    PageMoveDistance(PageManager.MoveDir, xBuf);
                }
                PageManager.MoveDir = PageLeft;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }else if(xBuf < 0)
            {
                if(PageManager.MoveDir == PageLeft)
                {
                    PageMoveDistance(PageManager.MoveDir, xBuf);
                }
                PageManager.MoveDir = PageRight;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }else{
                PageManager.MoveDir = PageNone;
                PageMoveDistance(PageManager.MoveDir, xBuf);
            }
        }break;

        case LV_DIR_VER:{
            // DEBUG("LV_DIR_VER [%d]\r\n", PageManager.pos_y);
            if(yBuf > 0)
            {
                if(PageManager.MoveDir == PageDown)
                {
                    PageMoveDistance(PageManager.MoveDir, yBuf);
                }
                PageManager.MoveDir = PageUp;
                PageMoveDistance(PageManager.MoveDir, yBuf);
            }else if(yBuf < 0)
            {
                if(PageManager.MoveDir == PageUp)
                {
                    PageMoveDistance(PageManager.MoveDir, yBuf);
                }
                PageManager.MoveDir = PageDown;
                PageMoveDistance(PageManager.MoveDir, yBuf);
            }else{
                PageManager.MoveDir = PageNone;
                PageMoveDistance(PageManager.MoveDir, yBuf);
            }
        }break;

        default:{
        }break;
    }
}

// 初始化页面管理器
void PM_Init(void)
{
    DEBUG("InitPageManager\r\n");

    PageManager.State       = LV_DIR_NONE;
    PageManager.Dir         = LV_DIR_NONE;
    PageManager.MoveDir     = PageNone;
    PageManager.pos_x       = 0;
    PageManager.pos_y       = 0;
    PageManager.LimitSize = PageLimit;
    if(PageManager.LimitSize > 100)
    {
        PageManager.LimitSize = 100;
    }else if(PageManager.LimitSize < 1){
        PageManager.LimitSize = 1;
    }
    PageManager.LimitSize   = WIDTH * HEIGHT / 100 * PageManager.LimitSize;
    DEBUG("LimitSize [%d] !!!\r\n", PageManager.LimitSize);

    lv_style_init(&PageManager.DefaultStyle);
    lv_style_set_pad_all(&PageManager.DefaultStyle, 0);
    lv_style_set_bg_opa(&PageManager.DefaultStyle, LV_OPA_0);
    lv_style_set_border_width(&PageManager.DefaultStyle, 0);
    lv_style_set_radius(&PageManager.DefaultStyle, 0);
    lv_style_set_align(&PageManager.DefaultStyle, LV_ALIGN_CENTER);

    PageManager.obj = lv_obj_create(NULL);
    lv_obj_add_style(PageManager.obj, &PageManager.DefaultStyle, 0);
    lv_obj_set_size(PageManager.obj, WIDTH, HEIGHT);
    lv_obj_clear_flag(PageManager.obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(PageManager.obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_event_cb(PageManager.obj, draging_event_handler, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(PageManager.obj, dragend_event_handler, LV_EVENT_RELEASED, NULL);

    PageManager.BackGround = lv_obj_create(PageManager.obj);
    lv_obj_add_style(PageManager.BackGround, &PageManager.DefaultStyle, 0);
    lv_obj_set_style_bg_opa(PageManager.BackGround, LV_OPA_100, 0);
    lv_obj_set_size(PageManager.BackGround, LV_PCT(100), LV_PCT(100));
    lv_obj_move_background(PageManager.BackGround);

    lv_anim_init(&PageManager.Anim);
    lv_anim_set_var(&PageManager.Anim, &PageManager);
    lv_anim_set_repeat_delay(&PageManager.Anim, 0xff);
}

// 开始页面管理器
void PM_Start(PageTypeHandle* Page)
{
    PM_SetHomePage(Page);
    DEBUG("PageManager Is Start\r\n");
}

// 添加页面
void PM_AddPage(PageTypeHandle* Page, void (*InitPage)(lv_obj_t* page), void (*DeinitPage)(lv_obj_t* page), enum Page_Id id)
{
    if(Page == NULL)
    {
        DEBUG("Add Page Failed, Page Is Null\r\n");
        return;
    }
    Page->State         = VAILD;
    Page->InitPage      = InitPage;
    Page->DeinitPage    = DeinitPage;
    Page->Up.Page       = NULL;
    Page->Up.Mode       = LOAD_ANIM_NONE;
    Page->Down.Page     = NULL;
    Page->Down.Mode     = LOAD_ANIM_NONE;
    Page->Left.Page     = NULL;
    Page->Left.Mode     = LOAD_ANIM_NONE;
    Page->Right.Page    = NULL;
    Page->Right.Mode    = LOAD_ANIM_NONE;
    Page->id            = id;
}

// 关闭页面
void PM_ClosePage(PageTypeHandle* SourcePage, enum PageDir Dir)
{
    PageTypeHandle* Page = GetDirPage(SourcePage, Dir);
    if(Page != NULL)
    {
        if(Page->State == VAILD_AND_CREATED)
        {
            Page->DeinitPage(Page->obj);
            lv_obj_del(Page->obj);
            Page->State = VAILD;
        }else{
            DEBUG("Cannot Close No Created Page\r\n");
        }
    }else{
        DEBUG("Cannot Close Non-Existent Page\r\n");
    }
}

// 删除页面
void PM_DelPage(PageTypeHandle* SourcePage, enum PageDir Dir)
{
    PageTypeHandle* Page = GetDirPage(SourcePage, Dir);
    SetDirMode(SourcePage, Dir, LOAD_ANIM_NONE);

    if(Page != NULL)
    {
        if(Page->State == VAILD_AND_CREATED)
        {
            Page->DeinitPage(Page->obj);
            lv_obj_del(Page->obj);
            Page->State = VAILD;
        }
        Page->State         = INVAILD;
        Page->obj           = NULL;
        Page->InitPage      = NULL;
        Page->DeinitPage    = NULL;
        Page->Up.Page       = NULL;
        Page->Up.Mode       = LOAD_ANIM_NONE;
        Page->Down.Page     = NULL;
        Page->Down.Mode     = LOAD_ANIM_NONE;
        Page->Left.Page     = NULL;
        Page->Left.Mode     = LOAD_ANIM_NONE;
        Page->Right.Page    = NULL;
        Page->Right.Mode    = LOAD_ANIM_NONE;
    }else{
        DEBUG("Cannot Delete Non-Existent Page\r\n");
    }
}

// 设置页面切换
void PM_SetPageMoveMode(PageTypeHandle* SourcePage, enum PageDir Dir, PageTypeHandle* TargetPage, enum MoveMode Mode)
{
    if((SourcePage == NULL) | (SourcePage->State == INVAILD))
    {
        DEBUG("SourcePage Is No Add To PageManager\r\n");
        return;
    }

    if((TargetPage == NULL) | (TargetPage->State == INVAILD))
    {
        DEBUG("TargetPage Is No Add To PageManager\r\n");
        return;
    }

    if(Mode == LOAD_ANIM_NONE)
    {
        DEBUG("Switch Is No Anim [%d]\r\n", Mode);
        return;
    }

    SetDirPage(SourcePage, Dir, TargetPage);
    SetDirMode(SourcePage, Dir, Mode);
}

// 设置主页面
void PM_SetHomePage(PageTypeHandle* Page)
{
    PageTypeHandle* PageBuf;
    if(Page == NULL)
    {
        DEBUG("PM_SetHomePage Failed Page Not Add PageManager\r\n");
        return;
    }

    switch (Page->State)
    {
        case INVAILD:{
            DEBUG("PM_SetHomePage Failed Page Not Add PageManager\r\n");
            return;
        }break;

        case VAILD:{
            PageBuf = Page;
            PageBuf->obj = lv_obj_create(PageManager.obj);
            lv_obj_add_style(PageBuf->obj, &PageManager.DefaultStyle, 0);
            lv_obj_set_size(PageBuf->obj, LV_PCT(100), LV_PCT(100));
            lv_obj_clear_flag(PageBuf->obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(PageBuf->obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_add_flag(PageBuf->obj, LV_OBJ_FLAG_EVENT_BUBBLE);
            PageBuf->InitPage(PageBuf->obj);
            PageBuf->State = VAILD_AND_CREATED;
            
            if(PageManager.HomePage != NULL)
            {
                // Page的VAILD状态说明与HomePage大概率不相邻
                // HomePage若存在，则清除所有旧页面
                DEBUG("Clear All Old HomePage\r\n");
                PM_ClosePage(PageManager.HomePage, PageUp);
                PM_ClosePage(PageManager.HomePage, PageDown);
                PM_ClosePage(PageManager.HomePage, PageLeft);
                PM_ClosePage(PageManager.HomePage, PageRight);
                PM_ClosePage(PageManager.HomePage, PageNone);
            }
        }break;

        case VAILD_AND_CREATED:{
            if(PageManager.HomePage != NULL)
            {
                // Page的VAILD_AND_CREATED状态说明与HomePage相邻
                // HomePage若存在，则清除除了自己的其他旧页面
                DEBUG("Clear Old HomePage But Me\r\n");
                enum PageState StateBuf = GetDirState(PageManager.HomePage, PageUp);
                if((StateBuf == VAILD_AND_CREATED) & (PageManager.HomePage->Up.Page != Page))
                {
                    DEBUG("Close Old HomePage's PageUp\r\n");
                    PM_ClosePage(PageManager.HomePage, PageUp);
                }

                StateBuf = GetDirState(PageManager.HomePage, PageDown);
                if((StateBuf == VAILD_AND_CREATED) & (PageManager.HomePage->Down.Page != Page))
                {
                    DEBUG("Close Old HomePage's PageDown\r\n");
                    PM_ClosePage(PageManager.HomePage, PageDown);
                }

                StateBuf = GetDirState(PageManager.HomePage, PageLeft);
                if((StateBuf == VAILD_AND_CREATED) & (PageManager.HomePage->Left.Page != Page))
                {
                    DEBUG("Close Old HomePage's PageLeft\r\n");
                    PM_ClosePage(PageManager.HomePage, PageLeft);
                }

                StateBuf = GetDirState(PageManager.HomePage, PageRight);
                if((StateBuf == VAILD_AND_CREATED) & (PageManager.HomePage->Right.Page != Page))
                {
                    DEBUG("Close Old HomePage's PageRight\r\n");
                    PM_ClosePage(PageManager.HomePage, PageRight);
                }
            }
        }break;

        default:{
        }break;
    }
    PageManager.Dir = LV_DIR_NONE;

    if(Page->Up.Mode != LOAD_ANIM_NONE)
    {
        PageBuf = Page->Up.Page;
        switch (PageBuf->State)
        {
            case INVAILD:{
                DEBUG("HomePage's UpPage Is INVAILD\r\n");
            }break;

            case VAILD:{
                DEBUG("HomePage's UpPage Is VAILD\r\n");
                PageBuf->obj = lv_obj_create(PageManager.obj);
                lv_obj_add_style(PageBuf->obj, &PageManager.DefaultStyle, 0);
                lv_obj_set_size(PageBuf->obj, LV_PCT(100), LV_PCT(100));
                lv_obj_clear_flag(PageBuf->obj, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_set_scrollbar_mode(PageBuf->obj, LV_SCROLLBAR_MODE_OFF);
                lv_obj_add_flag(PageBuf->obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_TOP_MID, 0, 0);
                PageBuf->InitPage(PageBuf->obj);
                PageBuf->State = VAILD_AND_CREATED;
                PageManager.Dir |= LV_DIR_TOP;
            }break;

            case VAILD_AND_CREATED:{
                DEBUG("HomePage's UpPage Is Create\r\n");
                PageManager.Dir |= LV_DIR_TOP;
                if(Page->Up.Mode == LOAD_ANIM_OVER || Page->Up.Mode == LOAD_ANIM_LEAVE) {
                    break;
                }
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_TOP_MID, 0, 0);
            }break;
        }
    }
    
    if(Page->Down.Mode != LOAD_ANIM_NONE)
    {
        PageBuf = Page->Down.Page;
        switch (PageBuf->State)
        {
            case INVAILD:{
                DEBUG("HomePage's DownPage Is INVAILD\r\n");
            }break;

            case VAILD:{
                DEBUG("HomePage's DownPage Is VAILD\r\n");
                PageBuf->obj = lv_obj_create(PageManager.obj);
                lv_obj_add_style(PageBuf->obj, &PageManager.DefaultStyle, 0);
                lv_obj_set_size(PageBuf->obj, LV_PCT(100), LV_PCT(100));
                lv_obj_clear_flag(PageBuf->obj, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_set_scrollbar_mode(PageBuf->obj, LV_SCROLLBAR_MODE_OFF);
                lv_obj_add_flag(PageBuf->obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
                PageBuf->InitPage(PageBuf->obj);
                PageBuf->State = VAILD_AND_CREATED;
                PageManager.Dir |= LV_DIR_BOTTOM;
            }break;

            case VAILD_AND_CREATED:{
                DEBUG("HomePage's DownPage Is Create\r\n");
                PageManager.Dir |= LV_DIR_BOTTOM;
                if(Page->Down.Mode == LOAD_ANIM_OVER || Page->Down.Mode == LOAD_ANIM_LEAVE) {
                    break;
                }
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
            }break;
        }
    }

    
    if(Page->Left.Mode != LOAD_ANIM_NONE)
    {
        PageBuf = Page->Left.Page;
        switch (PageBuf->State)
        {
            case INVAILD:{
                DEBUG("HomePage's LeftPage Is INVAILD\r\n");
            }break;

            case VAILD:{
                DEBUG("HomePage's LeftPage Is VAILD\r\n");
                PageBuf->obj = lv_obj_create(PageManager.obj);
                lv_obj_add_style(PageBuf->obj, &PageManager.DefaultStyle, 0);
                lv_obj_set_size(PageBuf->obj, LV_PCT(100), LV_PCT(100));
                lv_obj_clear_flag(PageBuf->obj, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_set_scrollbar_mode(PageBuf->obj, LV_SCROLLBAR_MODE_OFF);
                lv_obj_add_flag(PageBuf->obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_LEFT_MID, 0, 0);
                PageBuf->InitPage(PageBuf->obj);
                PageBuf->State = VAILD_AND_CREATED;
                PageManager.Dir |= LV_DIR_LEFT;
            }break;

            case VAILD_AND_CREATED:{
                DEBUG("HomePage's LeftPage Is Create\r\n");
                PageManager.Dir |= LV_DIR_LEFT;
                if(Page->Left.Mode == LOAD_ANIM_OVER || Page->Left.Mode == LOAD_ANIM_LEAVE) {
                    break;
                }
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_LEFT_MID, 0, 0);
            }break;
        }
    }

    
    if(Page->Right.Mode != LOAD_ANIM_NONE)
    {
        PageBuf = Page->Right.Page;
        switch (PageBuf->State)
        {
            case INVAILD:{
                DEBUG("HomePage's RightPage Is INVAILD\r\n");
            }break;

            case VAILD:{
                DEBUG("HomePage's RightPage Is VAILD\r\n");
                PageBuf->obj = lv_obj_create(PageManager.obj);
                lv_obj_add_style(PageBuf->obj, &PageManager.DefaultStyle, 0);
                lv_obj_set_size(PageBuf->obj, LV_PCT(100), LV_PCT(100));
                lv_obj_clear_flag(PageBuf->obj, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_set_scrollbar_mode(PageBuf->obj, LV_SCROLLBAR_MODE_OFF);
                lv_obj_add_flag(PageBuf->obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
                PageBuf->InitPage(PageBuf->obj);
                PageBuf->State = VAILD_AND_CREATED;
                PageManager.Dir |= LV_DIR_RIGHT;
            }break;

            case VAILD_AND_CREATED:{
                DEBUG("HomePage's RightPage Is Create\r\n");
                PageManager.Dir |= LV_DIR_RIGHT;
                if(Page->Right.Mode == LOAD_ANIM_OVER || Page->Right.Mode == LOAD_ANIM_LEAVE) {
                    break;
                }
                lv_obj_align_to(PageBuf->obj, Page->obj, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
            }break;
        }
    }
    PageManager.HomePage = Page;
}

// 页面切换
void PM_PageMove(enum PageDir Dir)
{
    DEBUG("PM_PageMove [%d]\r\n", Dir);
    PageManager.MoveDir = Dir;
    AnimToPage(Dir, 0);
}

// 获取管理器背景层OBJ指针
lv_obj_t* PM_GetBackGroudObj(void)
{
    if(PageManager.BackGround == NULL)
    {
        DEBUG("GetBackGroudObj Failed\r\n");
        return NULL;
    }else{
        return PageManager.BackGround;
    }
}


// 获取管理器主体OBJ指针
lv_obj_t* PM_GetObj(void)
{
    if(PageManager.obj == NULL)
    {
        DEBUG("GetObj Failed\r\n");
        return NULL;
    }else{
        return PageManager.obj;
    }
}







