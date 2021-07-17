#include "TAKEnhancedDll/Utils.hpp"

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1)
{
    std::unordered_map<T2, T1> map2;

    std::for_each(map1.begin(), map1.end(), [&](std::pair<T1, T2> elem) {
        map2.insert(std::pair<T2, T1>(elem.second, elem.first));
        });

    return map2;
}

std::vector<std::string> get_files_from_path(std::filesystem::path& path, const char* extension)
{
    std::vector<std::string> hpi_files;

    for (std::filesystem::directory_entry dir_entry : std::filesystem::directory_iterator(path)) {
        if (dir_entry.is_regular_file()) {
            std::string filename = dir_entry.path().filename().string();
            std::string file_extension = dir_entry.path().filename().extension().string();

            if (str_equals_str(file_extension.c_str(), extension)) {
                hpi_files.push_back(filename);
            }
        }
    }

    return hpi_files;
}
