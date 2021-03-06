/*
 * Copyright (C) 2015 Adrien Devresse <adrien.devresse@epfl.ch>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#ifndef MVD2_HPP
#define MVD2_HPP

/**
 * @file mvd2.hpp
 *
 * mvd2 file parser
 *
 * */


#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>


///
/// MVD2 parsing / helper functions
///
namespace MVD2{

///
/// \brief data type in the current MVD2 line
///
enum DataSet{
    None = 0,
    NeuronLoaded = 1,
    MicroBoxData = 2,
    MiniColumnsPosition = 3,
    CircuitSeeds = 4,
    MorphTypes = 5,
    ElectroTypes = 6
};


class MVD2File{
public:
    MVD2File(const std::string & filename) :
        _filename(filename),
        _nb_neuron(0),
        _nb_morpho_type(0),
        _nb_morpho(0){

    }

    ///
    /// \brief getNbMorpho
    /// \return number of morphologies in MVD file
    size_t getNbMorphoType();

    ///
    size_t getNbMorpho();

    ///
    /// \brief getNbNeuron
    /// \return number of neurons in this MVD file
    ///
    size_t getNbNeuron();

    ///
    ///
    ///
    template <typename Callback>
    void parse(Callback & line_parser);

private:
    std::string _filename;
    size_t _nb_neuron;
    size_t _nb_morpho_type;
    size_t _nb_morpho;

    void init_counter();
};

//
// parsing functions for use in callback
//

/// parse a line identified as a neuron information line (NeuronLoaded)
///  The parsing is done in float simple precision for position and rotation
///
void parseNeuronLine(const char* line, std::string & name, int& database, int &column, int &minicolumn, int &layer,
                     int &morphologytype, int &electrophysiology_type,
                     std::vector<float> & xyzr, std::string & metype);

/// parse a line identified as random seed initializer (CircuitSeeds)
void parseSeedInitLine(const char *line, double &seed1, double &seed2, double &seed3);

/// parse a line identified as en cell electrical type (ElectroTypes)
void parseElectroTypeLine(const char *line, std::string &electroType);

/// parse a line identified as morph type (MorphType)
void parseMorphTypeLine(const char* line, std::string & name, std::string & name2, std::string & morphClass);

}


#include "bits/mvd2_misc.hpp"

#endif // MVD2_HPP
