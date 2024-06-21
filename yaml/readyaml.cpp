#include <iostream>      // 包含标准输入输出流库，用于输入输出操作
#include <yaml-cpp/yaml.h> // 包含 yaml-cpp 库，用于解析 YAML 文件

// 声明一个函数，用于读取指定 YAML 文件中的 acl_path 值
std::string getAclPath(const std::string& filename) {
    try {
        YAML::Node config = YAML::LoadFile(filename); // 尝试加载 YAML 文件
        if (config["register"] && config["register"]["acl_path"]) {
            // 检查 register 键和 acl_path 是否存在
            return config["register"]["acl_path"].as<std::string>(); // 返回 acl_path 的值
        } else {
            // 如果键不存在，返回一个说明性的错误信息
            return "Register or acl_path not found in YAML file.";
        }
    } catch (const YAML::BadFile& e) {
        // 捕获并处理文件读取异常
        return "Failed to open YAML file: " + std::string(e.what());
    } catch (const YAML::ParserException& e) {
        // 捕获并处理解析 YAML 时的异常
        return "Failed to parse YAML file: " + std::string(e.what());
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        // 检查命令行参数数量是否正确
        std::cerr << "Usage: " << argv[0] << " <yaml_file>" << std::endl;
        return 1; // 如果参数不正确，返回错误码 1
    }

    // 读取 YAML 文件并获取 acl_path 值
    std::string aclPath = getAclPath(argv[1]);
    std::cout << "ACL Path: " << aclPath << std::endl; // 输出 acl_path 值

    return 0; // 程序正常结束
}
