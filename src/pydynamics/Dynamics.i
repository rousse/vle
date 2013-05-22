/* Module Dynamics */
%module(directors="1") testDynamics
%{
 /**** includes ****/ 
#include <vle/DllDefines.hpp>
#include <vle/devs/Time.hpp>
#include <vle/devs/InitEventList.hpp>
#include <vle/devs/ExternalEvent.hpp>
//#include <vle/devs/ExternalEventList.hpp>
#include <vle/devs/ObservationEvent.hpp>
#include <vle/vpz/AtomicModel.hpp>
#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>
#include <vle/utils/PackageTable.hpp>
#include <vle/version.hpp>
//#include <string>

//#include <vle/devs/Dynamics.hpp>
//#include <vle/utils/Path.hpp>
#include <vle/utils/Package.hpp>
#include "testDynamics.hpp"

namespace vle { namespace devs {
	class RootCoordinator;
	typedef utils::PackageTable::index PackageId;
	extern int b(int i);

}}
%}

%{
using namespace vle;
using namespace vle::devs;
using namespace vle::value;
using namespace vle::vpz;
using namespace vle::utils;
using namespace std;
%}

%include <std_string.i>
%include <std_vector.i>
//%include "std_map.i"

// Test de function ********************************

#define VLE_API
namespace vle { namespace devs {
	class RootCoordinator;
	typedef utils::PackageTable::index PackageId;
	extern int b(int i);

    	class VLE_API DynamicsInit
    	{
    	public:
        	DynamicsInit(const vpz::AtomicModel& model,
                     PackageId packageid)
            	: m_model(model), m_packageid(packageid);

        	virtual ~DynamicsInit();

        	const vpz::AtomicModel& model() const;
        	PackageId packageid() const;

    	private:
        	const vpz::AtomicModel&       m_model;
        	PackageId                       m_packageid;
    	};

	class VLE_API Dynamics
    	{
    	public:
        	Dynamics(const DynamicsInit& init,
                 	const vle::devs::InitEventList&)
            	: m_model(init.model()), m_packageid(init.packageid());

        	virtual ~Dynamics();
		
		//virtual vle::devs::Time init(const vle::devs::Time& /* time */);
	private:
        	const vpz::AtomicModel& m_model; 
		PackageId m_packageid;
	};

}}
//**************************************************

/**** includes ****/ 
#define DEVS_DYNAMICS_HPP
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

%include "testDynamics.hpp"
%include <vle/DllDefines.hpp>
%include <vle/devs/Time.hpp>
%include <vle/devs/InitEventList.hpp>
%include <vle/devs/ExternalEvent.hpp>

//%include <vle/devs/ExternalEventList.hpp>
//************* Erreur de l'include EternalEventList.hpp *********************************
//vle::devs::operator<<(std::basic_ostream<char, std::char_traits<char> >&, std::vector<vle::devs::ExternalEvent*, std::allocator<vle::devs::ExternalEvent*> > const&)
//****************************************************************************************

%include <vle/devs/ObservationEvent.hpp>
%include <vle/vpz/AtomicModel.hpp>
%include <vle/value/Value.hpp>
%include <vle/value/Double.hpp>
%include <vle/value/Integer.hpp>
%include <vle/value/Boolean.hpp>
%include <vle/value/String.hpp>
%include <vle/utils/PackageTable.hpp>
%include <vle/version.hpp>
//%include <string>

//%include <vle/devs/Dynamics.hpp>
//%include <vle/utils/Path.hpp>
%include <vle/utils/Package.hpp>
