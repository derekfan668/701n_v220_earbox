import os

# 路径信息
current_path = os.getcwd()
path_gpu2d = r'lv_charging_case/GPU2D/'

# 存储.c文件和.h文件的列表
c_files = []
h_files = []
directories_with_h_files = set()  # 使用集合来去除重复的路径

# 遍历当前路径及其子路径
for root, dirs, files in os.walk(current_path):

    # if path_ui in root or path_lvgl in root or path_lvgl_porting in root:
    for file in files:
        if file.endswith(".c"):
            # 获取相对路径并替换反斜杠为斜杠
            c_file = os.path.relpath(os.path.join(root, file), current_path).replace("\\", "/")
            c_files.append(c_file)
        elif file.endswith(".h"):
            # 记录包含.h文件的路径
            directory_with_h_file = os.path.relpath(root, current_path).replace("\\", "/")
            directories_with_h_files.add(directory_with_h_file)

# 将输出保存到txt文件
output_file_path = "gpu2d.mk"
with open(output_file_path, "w", encoding = 'utf-8') as output_file:
    output_file.write("c_SRC_FILES += \\ \n")
    for c_file in c_files:
        output_file.write("\t" + path_gpu2d + c_file + " \\" + "\n")

    output_file.write("\n")

    output_file.write("INCLUDES += \\ \n")
    for directory_with_h_file in directories_with_h_files:
        output_file.write("\t" + "-I" + path_gpu2d + directory_with_h_file +  " \\" + "\n")

# print(f"输出已保存到文件 {output_file_path}")
