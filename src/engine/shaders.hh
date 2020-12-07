//
// Created by bparsy on 6/8/20.
//

#ifndef FIRE_SHADERS_HH
#define FIRE_SHADERS_HH

#include <string>

namespace shd {
    const std::string base_dir = "../res/shaders/";

    std::string vtx(std::string const& name) {
        return base_dir + "vertex/" + name + ".shd";
    }

    std::string fgt(std::string const& name) {
        return base_dir + "fragment/" + name + ".shd";
    }

    std::string gmt(std::string const& name) {
        return base_dir + "geometry/" + name + ".shd";
    }

    std::string cpt(std::string const& name) {
        return base_dir + "compute/" + name + ".shd";
    }

    std::string tess_ctrl(std::string const& name) {
        return base_dir + "tesselation/" + name + "_ctrl.shd";
    }

    std::string tess_eval(std::string const& name) {
        return base_dir + "tesselation/" + name + "_eval.shd";
    }
}

#endif //FIRE_SHADERS_HH
