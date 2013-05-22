/*
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems.
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2013 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2013 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2013 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and
 * contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef DEVS_DYNAMICS_HPP
#define DEVS_DYNAMICS_HPP

#include <vle/DllDefines.hpp>
#include <vle/devs/Time.hpp>
#include <vle/devs/InitEventList.hpp>
#include <vle/devs/ExternalEvent.hpp>
#include <vle/devs/ExternalEventList.hpp>
#include <vle/devs/ObservationEvent.hpp>
#include <vle/vpz/AtomicModel.hpp>
#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>
#include <vle/utils/PackageTable.hpp>
#include <vle/version.hpp>
#include <string>

#define DECLARE_DYNAMICS(mdl)                                           \
    extern "C" {                                                        \
        VLE_MODULE vle::devs::Dynamics*                                 \
        vle_make_new_dynamics(const vle::devs::DynamicsInit& init,      \
                              const vle::devs::InitEventList& events)   \
        {                                                               \
            return new mdl(init, events);                               \
        }                                                               \
                                                                        \
        VLE_MODULE void                                                 \
        vle_api_level(vle::uint32_t* major,                             \
                      vle::uint32_t* minor,                             \
                      vle::uint32_t* patch)                             \
        {                                                               \
            *major = VLE_MAJOR_VERSION;                                 \
            *minor = VLE_MINOR_VERSION;                                 \
            *patch = VLE_PATCH_VERSION;                                 \
        }                                                               \
    }

namespace vle { namespace devs {

    class RootCoordinator;

    /**
     * @brief A PackageId defines a reference to an element of the
     * vle::utils::PackageTable.
     */
    typedef utils::PackageTable::index PackageId;

    class VLE_API DynamicsInit
    {
    public:
        DynamicsInit(const vpz::AtomicModel& model,
                     PackageId packageid)
            : m_model(model), m_packageid(packageid)
        {}

        virtual ~DynamicsInit()
        {}

        const vpz::AtomicModel& model() const { return m_model; }
        PackageId packageid() const { return m_packageid; }

    private:
        const vpz::AtomicModel&       m_model;
        PackageId                       m_packageid;
    };

    /**
     * @brief Dynamics class represent a part of the DEVS simulator. This class
     * must be inherits to build simulation components.
     */
    class VLE_API Dynamics
    {
    public:
        /**
         * @brief Constructor of Dynamics for an atomic model.
         *
         * @param init The initialiser of Dynamics.
         * @param events The parameter from the experimental frame.
         */
        Dynamics(const DynamicsInit& init,
                 const vle::devs::InitEventList&  /* events */)
            : m_model(init.model()), m_packageid(init.packageid())
        {}

	/**
	 * @brief Destructor (nothing to do)
	 */
        virtual ~Dynamics()
        {}

    private:
        const vpz::AtomicModel& m_model; /**< A constant reference to the
                                             atomic model node of the graph.
                                               */

        PackageId m_packageid; /**< An iterator to std::set of the
                                 vle::utils::PackageTable. */
    };
}}

#endif
