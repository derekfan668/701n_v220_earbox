#include "custom.h"

static lv_timer_t *screen_refresh_timer = NULL;



//-------------------------------------------------------------------------------------------
//-----------------------------------抢断页面管理链表----------------------------------------
//-------------------------------------------------------------------------------------------

typedef struct ScreenNode {
    lv_obj_t *screen;
    int Screen_Id;
    int init_flag;
    void (*Init)();
    void (*Deinit)();
    void (*Load)();
    void (*Refresh)();
    struct ScreenNode * next;
} ScreenNode;

static ScreenNode * head = NULL;

static bool is_exists(int Screen_Id) 
{
    ScreenNode * current = head;
    while (current != NULL) {
        if (current->Screen_Id == Screen_Id) {
            return true;
        }
        current = current->next;
    }
    return false;
}


static void add_node(void (*Init)(), void (*Deinit)(), void (*Load)(), void (*Refresh)(),int Screen_Id) 
{
    ScreenNode * new_node = (ScreenNode *)malloc(sizeof(ScreenNode));
    new_node->Screen_Id = Screen_Id;
    new_node->init_flag = false;
    new_node->Init = Init;
    new_node->Deinit = Deinit;
    new_node->Load = Load;
    new_node->Refresh = Refresh;
    new_node->next = NULL;

    if (head == NULL || head->Screen_Id < Screen_Id) {
        // 插入到链表头部
        new_node->next = head;
        head = new_node;
    } else {
        // 找到插入点
        ScreenNode * current = head;
        while (current->next != NULL && current->next->Screen_Id >= Screen_Id) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


static void del_node(int Screen_Id) 
{
    ScreenNode * current = head;
    ScreenNode * prev = NULL;

    while (current != NULL) {
        if (current->Screen_Id == Screen_Id) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

static void free_list() {
    ScreenNode * current = head;
    while (current != NULL) {
        ScreenNode * next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

//-------------------------------------------------------------------------------------------
//-----------------------------------对外接口------------------------------------------------
//-------------------------------------------------------------------------------------------

lv_obj_t *root_screen = NULL;


void screen_list_clean()
{
    free_list();
}


void screen_list_add(void (*Init)(), void (*Deinit)(), void (*Load)(), void (*Refresh)(), int Screen_Id)
{
    if(Init == NULL || Deinit == NULL || Load == NULL ){
        r_printf("[error] screen_list_add: Init OR Deinit OR Load == NULL!!!");
        return;
    }

    if(Screen_Id < 0 || Screen_Id >= SCREEN_PRIO_MAX){
        r_printf("[error] screen_list_add : Screen_Id not match!!!");
        return;
    }

    ScreenNode * current = head;

    if(current == NULL){
        root_screen = lv_scr_act();     //记录被抢断的非抢断页面
    }else{
        if (is_exists(Screen_Id)) {
            return;
        }
    }

    add_node(Init, Deinit, Load, Refresh, Screen_Id);

    screen_list_printf();
}


void screen_list_printf()
{
    printf("-----------------------");
    ScreenNode * current = head;
    int count = 0;
    while (current != NULL) {
        printf("[%d]:Screen_Id:%d\n", count, current->Screen_Id);
        count++;
        ScreenNode * next = current->next;
        current = next;
    }
    printf("-----------------------");
}


void screen_list_del(int Screen_Id)
{
    if(Screen_Id < 0 || Screen_Id >= SCREEN_PRIO_MAX){
        r_printf("[error] screen_list_del : Screen_Id not match!!!");
        return;
    }

    ScreenNode * current = head;

    if(current == NULL){
        return;
    }

    if(current->Screen_Id == Screen_Id){
        if(current->next == NULL){     //没有抢断页面，返回根页面
            if(root_screen){
                lv_scr_load(root_screen);
            }
        }else{

            // 初始化下一个页面
            if(!current->next->init_flag){
                if(current->next->Init){
                    current->next->Init();
                    current->next->init_flag = true;
                }
            }

            // 显示下一个页面
            if(current->next->Load){
                current->next->Load();
            }
        }

        // 把当前页面释放
        if(current->init_flag){
            if(current->Deinit){
                current->Deinit();
                current->init_flag = false;
            }
        }
    }

    del_node(Screen_Id);

    screen_list_printf();
}

void screen_list_refresh()
{
    static ScreenNode * previous = NULL;
    ScreenNode * current = head;
    if(current == NULL){
        return;
    }

    if(previous != current){

        // 初始化新页面
        if(!current->init_flag){
            if(current->Init){
                current->Init();
                current->init_flag = true;
            }
        }

        // 显示新页面
        if(current->Load){
            current->Load();
        }

        // 把其他页面释放
        ScreenNode * temp = current->next;
        while (temp != NULL) {
            if(temp->init_flag){
                if(temp->Deinit){
                    temp->Deinit();
                    temp->init_flag = false;
                }
            }

            ScreenNode * next = temp->next;
            temp = next;
        }

        previous = current;
    }

    if(current->Refresh){
        current->Refresh();
    }
}




static void screen_refresh_timer_cb()
{

    screen_call_check();
    screen_charging_check();

    screen_list_refresh();

}

void lv_screen_refresh_start()
{
    if (!screen_refresh_timer) {
        screen_refresh_timer = lv_timer_create(screen_refresh_timer_cb, SCREEN_REFRESH_INTERVAL, NULL);
    }
}

