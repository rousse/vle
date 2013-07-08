/*
 * @file PyDynamics.cpp
 *
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2007 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2011 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2011 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <vle/utils/Path.hpp>
#include <vle/utils/Package.hpp>

#include "PyDynamics.hpp"

namespace pydynamics {

PyDynamics::PyDynamics(const vle::devs::DynamicsInit& model,
                       const vle::devs::InitEventList& events) :
            vle::devs::Dynamics(model, events),
            m_initevents(events),
            m_modelname("MyModelPy"), // par defaut
            m_pkgname("pydynamics") // par defaut
{ 
    std::cout << "PyDynamics constructeur \n";
        
    //.......

}

PyDynamics::~PyDynamics() 
{ 
    std::cout << "PyDynamics destructeur \n";

    //.......
}


void PyDynamics::finish() {
    std::cout << "PyDynamics::finish \n";

    //.......
};

vle::devs::Time PyDynamics::init(
        const vle::devs::Time& /* time */)
{
    std::cout << "PyDynamics::init \n";

    if ( m_initevents.exist("modelname") ){
	    m_modelname = vle::value::toString( m_initevents.get( "modelname" ));
    }
    if ( m_initevents.exist("pkgname") ){
	    m_pkgname = vle::value::toString( m_initevents.get( "pkgname" ));
    }
    std::cout << "\n";
    std::cout << "nom du modele python : " << m_modelname << ", ";
    std::cout << "nom du paquet du modele python : " << m_pkgname << ", ";
    std::cout << "le code python " << m_modelname << ".py doit etre installe sous " << m_pkgname << "/pythonsrc." << "\n";
    std::cout << "\n";

/* debut essai *******************************************/

    /* CODE TEMPORAIRE essai d'appel du code python */

    PyObject *pName, *pModule, *pDict, *pFunc, *pValue;

    // Initialize the Python Interpreter
    Py_Initialize();

    // Build the name object
    std::string model_library = m_modelname;
    pName = PyString_FromString(model_library.c_str());

    /* add pydynamics_wrapper and model path to pythonpath */
    //!!! revoir le codage des path relativement aux path de paquets

    // wrapper : "...vle-1.1/pkgs-1.1/pydynamics_wrapper/wrapping"
    std::string pydynamics_wrapper_library_path = utils::Path::buildDirname( vle::utils::Path::path().getHomeDir(), "pkgs-1.1" );
    pydynamics_wrapper_library_path = utils::Path::buildDirname( pydynamics_wrapper_library_path, "pydynamics_wrapper" );
    pydynamics_wrapper_library_path = utils::Path::buildDirname( pydynamics_wrapper_library_path, "wrapping" );

    // modele python : pythonsrc de son paquet "....vle-1.1/pkgs-1.1/pydynamics/pythonsrc"
    std::string model_library_path = utils::Path::buildDirname( vle::utils::Path::path().getHomeDir(), "pkgs-1.1" );
    model_library_path = utils::Path::buildDirname( model_library_path, m_pkgname );
    model_library_path = utils::Path::buildDirname( model_library_path, "pythonsrc" );

    std::string total_path = std::string(Py_GetPath()) + ":" + pydynamics_wrapper_library_path + ":" + model_library_path;
    PySys_SetPath((char *)total_path.c_str());

    // Load the module object
    pModule = PyImport_Import(pName);

    std::cout << "total_path vaut : " << total_path << "\n";
    std::cout << "AAAAAAAAAAAA_1 \n";

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);

    std::cout << "AAAAAAAAAAAA_2 \n";

    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, "model_is_it_ok");

    if (PyCallable_Check(pFunc)) {
        PyObject_CallObject(pFunc, NULL);
        std::cout << "CCC appel ok \n";
    } else {
        PyErr_Print();
        std::cout << "DDD appel not ok \n";
    }

    // Clean up
    Py_DECREF(pModule); 
    Py_DECREF(pName);

    // Finish the Python Interpreter
    Py_Finalize();

/* fin essai *********************************************/

    return vle::devs::infinity; //!!!
}


void PyDynamics::output(const vle::devs::Time& /* time */,
                     vle::devs::ExternalEventList& output) const
{
    std::cout << "PyDynamics::output \n";
    //....
}

vle::devs::Time PyDynamics::timeAdvance() const
{
    std::cout << "PyDynamics::timeAdvance \n";
    return vle::devs::infinity; //!!!
}


void PyDynamics::internalTransition(
        const vle::devs::Time& /* event */)
{
    std::cout << "PyDynamics::internalTransition \n";
    //....
}

void PyDynamics::externalTransition(
        const vle::devs::ExternalEventList& /* event */,
        const vle::devs::Time& /* time */)
{
    std::cout << "PyDynamics::externalTransition \n";
    //....
}

void PyDynamics::confluentTransitions( 
        const vle::devs::Time& time,
        const vle::devs::ExternalEventList& extEventlist) const
{
    std::cout << "PyDynamics::confluentTransition \n";
    //....
}


vle::value::Value* PyDynamics::observation(const vle::devs::ObservationEvent& event) const
{
    std::cout << "PyDynamics::observation \n";
    return 0; //!!!
}

} // namespace pydynamics
