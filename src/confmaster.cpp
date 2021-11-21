#include "confmaster/confmaster.hpp"

namespace am{
namespace conf{

    bool confmaster::load_config_file(){
        // open the config file
        std::ifstream config_file_stream{config_path_};

        try{
            config_file_stream >> raw_config_;
        }catch(const parse_error_type& be){
            error_msg_ = be.what();
            return false;
        }catch(const std::exception& ex){
            error_msg_ = ex.what();
            return false;
        }

        return true;
    }

};
};