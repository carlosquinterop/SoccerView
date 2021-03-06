//======================================================================//
//  This software is free: you can redistribute it and/or modify        //
//  it under the terms of the GNU General Public License Version 3,     //
//  as published by the Free Software Foundation.                       //
//  This software is distributed in the hope that it will be useful,    //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of      //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE..  See the      //
//  GNU General Public License for more details.                        //
//  You should have received a copy of the GNU General Public License   //
//  Version 3 in the file COPYING that came with this distribution.     //
//  If not, see <http://www.gnu.org/licenses/>                          //
//======================================================================//
//                                                                      //
//      Copyright (c) 2018 Carlos Quintero		                //
//      Universidad de los Andes - Bogota, Colombia                     //
//      quintero.carlos@uniandes.edu.co                                 //
//                                                                      //
//======================================================================//

SYSTEMS REQUIREMENTS 
	- Ubuntu 14.04 64 bits
	- Qt 5.7 Development Libraries
	- CMake 3.5.1

INSTALLATION:
	sudo apt-get install build-essential cmake qtdeclarative5-dev libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libqt5serialport5-dev 
	sudo add-apt-repository ppa:bladerf/bladerf
	sudo apt-get update
	sudo apt-get install bladerf

	Steps to install openCV
	https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html?highlight=installation

COMPILATION
	- mkdir build && cd build
	- cmake ..
	- make

EXECUTION
	- sudo ./bin/basicmotion
