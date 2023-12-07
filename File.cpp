#include "File.hpp"

namespace dc {

    File::File(std::string_view path) {
        this->path_ = std::filesystem::absolute(path);
    }

    File::File(File const &rhs) : path_(rhs.path_) {};

    std::string_view File::get_path() const {return this->path_;}

    std::string File::path_to_document() const
    {
        auto pos = this->path_.find_last_of('.');
        std::string tmp = this->path_.substr(0, pos) + "_doc_"
            + this->path_.substr(pos);
        return tmp;
    }

    bool File::is_valid() const {
        std::filesystem::file_status status = std::filesystem::status(this->path_);
        return std::filesystem::exists(status)
            && (status.permissions() & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
    }


}