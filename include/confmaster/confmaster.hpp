#ifndef CONFMASTER_CONFMASTER_HPP
#define CONFMASTER_CONFMASTER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <istream>

#include "nlohmann/json.hpp"

namespace rnd{
namespace conf{

    class confmaster{
        /**
         * @brief The purpose of this class is to parse json config files
         * without the boilerplate code of parsing each field into the
         * corresponding C++ type
         * 
         */
    public:
        using path_type = std::string;
        using raw_config_type = nlohmann::json;

        using base_error_type = nlohmann::json::exception;
        using parse_error_type = nlohmann::json::parse_error;
        using type_error_type = nlohmann::json::type_error;
        using out_of_range_type = nlohmann::json::out_of_range;
        using other_error_type = nlohmann::json::other_error;

        confmaster(
            const path_type& config_path
        ) :
            config_path_(config_path)
        {
            is_valid_ = load_config_file();
        }

        /**
         * @brief Returns if the config_manager is valid
         * and was able to load the config's json file
         * 
         * @return true 
         * @return false 
         */
        bool is_valid() const {
            return is_valid_;
        }

        /**
         * @brief If is_valid() returns false, this functions
         * returns the error message
         * 
         * @return const std::string& 
         */
        const std::string& error() const {
            return error_msg_;
        }

        /**
         * @brief Returns the full path of the config file
         * 
         * @return const path_type& 
         */
        const path_type& path() const {
            return config_path_;
        }

        /**
         * @brief Parses the json file to actual C++ types.
         * 
         * Example: auto t = parse<int, std::string>({"age", "name"})
         * This call will try to parse:
         *  - field "age" as an int
         *  - field "name" as a string
         * and return the parsed values.
         * So if in the config file: age: 4, name: "Beeblebrox"
         * The call will return a tuple with values of 4 (int) and "Beeblebrox" (string)
         * 
         * @tparam Args The types of the fields
         * @param fields The fields name you want to parse from the json file
         * @return std::tuple<Args...> The wanted fields values
         */
        template<typename... Args>
        std::tuple<Args...> parse(const std::vector<std::string>& fields){
            using Indices = std::make_index_sequence<sizeof...(Args)>;

            if (!is_valid()) return {};

            return parse_impl<Args...>(fields, Indices{});
        }

    private:
        /**
         * @brief Helper function for the parse function.
         * this functions basically iterates over the fields vector
         * and tries to parse them from the json file.
         * 
         * @tparam Args The types of the fields
         * @tparam I An index sequence [0, size of Args (number of elements)]
         * @param fields The fields you want to parse
         * @return std::tuple<Args...> 
         */
        template<typename... Args, size_t... I>
        std::tuple<Args...> parse_impl(
            const std::vector<std::string>& fields, 
            std::index_sequence<I...>
        ){
            std::tuple<Args...> help;
            return std::make_tuple(raw_config_.at(fields[I])
                .get<typename std::decay<decltype(std::get<I>(help))>::type>()...);
        }

        bool load_config_file();
        
        std::string error_msg_;
        bool is_valid_;

        path_type config_path_;
        nlohmann::json raw_config_;
    };

};
};

#endif