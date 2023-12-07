#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <filesystem>
#include <ranges>

namespace dc {

    class File {

        public:

            File(std::string_view path);
            ~File() = default;
            File(File const &rhs);
            File &operator=(File const &rhs) = delete;
            File(File const &&rhs) = delete;
            File &operator=(File const &&rhs) = delete;

            std::string_view get_path() const;
            std::string path_to_document() const;
            bool is_valid() const;

        private:

            std::string path_;

    };

}
#endif