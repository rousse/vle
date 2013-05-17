/* Module Dynamics */
%module(directors="1") testDynamics

%ignore vle::devs::operator<<;
%{
 /**** includes ****/ 
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
#include <vle/value/Map.hpp>
#include <vle/value/Set.hpp>
#include <vle/utils/PackageTable.hpp>
#include <vle/version.hpp>
//#include <vle/devs/Dynamics.hpp>
#include "testDynamics.hpp"
#include <Python.h>
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
%include <std_map.i>
%include <std_set.i>
%include <stdint.i> 
%include <stl.i>

%template(ExternalEventList) std::vector < vle::devs::ExternalEvent* >;
%typemap(out) const string& { $result = PyString_FromString($1.c_str()); }

#define VLE_API
namespace vle { namespace devs {

	class RootCoordinator;
	typedef utils::PackageTable::index PackageId;

	extern int b(int i);
    	
	class VLE_API DynamicsInit
    	{
    	public:
        	DynamicsInit(); 

        	virtual ~DynamicsInit();
    	};

	class VLE_API Dynamics
    	{
    	public:
        	Dynamics(const DynamicsInit& init);

        	virtual ~Dynamics();
		
		virtual vle::devs::Time init(const vle::devs::Time& /* time */);
	        virtual void output(const vle::devs::Time& /* time */,
                            vle::devs::ExternalEventList& /* output */) const;
	        virtual vle::devs::Time timeAdvance() const;
	        virtual void internalTransition(const vle::devs::Time& /* time */);
	        virtual void externalTransition(
	    		const vle::devs::ExternalEventList& /* event */,
            		const vle::devs::Time& /* time */);
        	virtual void confluentTransitions(
	    		const vle::devs::Time& time,
            		const vle::devs::ExternalEventList& extEventlist);
	        virtual vle::value::Value* observation(
	    		const vle::devs::ObservationEvent& /* event */) const;
		virtual void finish();
	        inline virtual bool isExecutive() const;
	        inline virtual bool isWrapper() const;
	        inline const vle::vpz::AtomicModel& getModel() const;
	        inline const std::string& getModelName() const;
	        inline vle::value::Double* buildDouble(double value) const;
	        inline vle::value::Integer* buildInteger(long value) const;
	        inline vle::value::Boolean* buildBoolean(bool value) const;
	        inline vle::value::String* buildString(const std::string& value) const;
	        vle::devs::ExternalEventList* noEvent() const;

		vle::devs::ExternalEvent* buildEvent(const std::string& portName) const;
	        vle::devs::ExternalEvent* buildEventWithADouble(
                           const std::string& portName,
                           const std::string& attributeName,
                           double attributeValue) const;
		vle::devs::ExternalEvent* buildEventWithAInteger(
			    const std::string & portName,
			    const std::string & attributeName,
			    long attributeValue) const;
		vle::devs::ExternalEvent* buildEventWithABoolean(
	    		const std::string & portName,
	    		const std::string & attributeName,
	    		bool attributeValue) const;
		vle::devs::ExternalEvent* buildEventWithAString(
	    		const std::string & portName,
	    		const std::string & attributeName,
	    		const std::string & attributeValue) const;

		std::string Dynamics::getPackageDir() const;
		std::string Dynamics::getPackageSimulatorDir() const;
		std::string Dynamics::getPackageSrcDir() const;
		std::string Dynamics::getPackageDataDir() const;
		std::string Dynamics::getPackageDocDir() const;
		std::string Dynamics::getPackageExpDir() const;
		std::string Dynamics::getPackageFile(const std::string& name) const;
		std::string Dynamics::getPackageLibFile(const std::string& name) const;
		std::string Dynamics::getPackageSrcFile(const std::string& name) const;
		std::string Dynamics::getPackageDataFile(const std::string& name) const;
		std::string Dynamics::getPackageDocFile(const std::string& name) const;
		std::string Dynamics::getPackageExpFile(const std::string& name) const;

	        inline PackageId packageid() const;


	private:
        	const vpz::AtomicModel& m_model; 
		PackageId m_packageid;
	};

}}

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
//%include <vle/devs/Dynamics.hpp>
%include <vle/DllDefines.hpp>
%include <vle/devs/Time.hpp>
%include <vle/devs/InitEventList.hpp>
%include <vle/devs/ExternalEvent.hpp>
%include <vle/devs/ExternalEventList.hpp>

%include <vle/devs/ObservationEvent.hpp>
%include <vle/vpz/AtomicModel.hpp>
%include <vle/value/Value.hpp>
%include <vle/value/Double.hpp>
%include <vle/value/Integer.hpp>
%include <vle/value/Boolean.hpp>
%include <vle/value/String.hpp>
%include <vle/value/Map.hpp>
%include <vle/value/Set.hpp>
%include <vle/utils/PackageTable.hpp>
%include <vle/version.hpp>
