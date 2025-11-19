import os
import zipfile

def zip_directory(zipf, directory):
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            zipf.write(file_path)  # 自动保留相对路径

def main():
    # 检查必要文件
    if not (os.path.isdir("src") and os.path.isfile("CMakeLists.txt")):
        print("错误：缺少 src 目录或 CMakeLists.txt 文件")
        return
    if not os.path.isdir("include"):
        print("错误：缺少 include 目录")
        return
    if not os.path.isfile("Calculator.g4"):
        print("错误：缺少 Calculator.g4 文件")
        return
    # 创建压缩包
    with zipfile.ZipFile("project.zip", "w", zipfile.ZIP_DEFLATED) as zipf:
        zip_directory(zipf, "src")
        zip_directory(zipf, "include")
        zipf.write("CMakeLists.txt")
        zipf.write("Calculator.g4")

    print("已生成压缩包：project.zip")

if __name__ == "__main__":
    main()