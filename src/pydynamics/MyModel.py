#-*- coding:utf-8 -*-

#******************************************************************************
#
# File MyModel.py
#
#------------------------------------------------------------------------------
#
# Un modele Dynamics partiel
#
#------------------------------------------------------------------------------
#
#******************************************************************************

import testDynamics
import convert

###############################################################################

class MyModel(testDynamics.Dynamics):
    
    # !!! dans constructeur MyModel, lire parametre dans init_events
    #def __init__( self, *args): 
    def __init__( self, modelinit, init_events ) :

        testDynamics.Dynamics.__init__( self, modelinit, init_events )

        print "__init__, type(modelinit) : ", type(modelinit)
        print "__init__, type(init_events ) : ", type(init_events )

        init_events_dict = convert.to_pyvalue( init_events )

        print "__init__, type(init_events_dict ) : ", type(init_events_dict )

        print "__init__, liste des parametres :"
        for p,val in init_events_dict.iteritems() :
            print "parametre de nom : ", p, " ; et de valeur(s) : ", val


    def output(self,time,events):

        # ecriture d'evenements dans events (external events)

        print ""
        print "--------------------------------------------"
        print "debut MyModel.output"
        print ""

        print "********************************************"
        print "Construction de 'Values'"

        #
        # !!! Value : imbriquer dans une Value map et list...
        #

        print ""
        mon_bool = False
        print "type(mon_bool) : ", type(mon_bool), " , valeur de mon_bool : ", mon_bool
        mon_bool_value = convert.to_vlevalue(mon_bool)
        print "type(mon_bool_value) : ", type(mon_bool_value)

        print ""
        mon_int = 77
        print "type(mon_int) : ", type(mon_int), " , valeur de mon_int : ", mon_int
        mon_int_value = convert.to_vlevalue(mon_int)
        print "type(mon_int_value) : ", type(mon_int_value)

        print ""
        mon_float = float(77)
        print "type(mon_float) : ", type(mon_float), " , valeur de mon_float : ", mon_float
        mon_float_value = convert.to_vlevalue(mon_float)
        print "type(mon_float_value) : ", type(mon_float_value)

        print ""
        mon_str = "mon_texte"
        print "type(mon_str) : ", type(mon_str), " , valeur de mon_str : ", mon_str
        mon_str_value = convert.to_vlevalue(mon_str)
        print "type(mon_str_value) : ", type(mon_str_value)

        print ""
        mon_dict = dict()
        mon_dict["cleA"] = "valeur_de_cleA"
        mon_dict["cleB"] = 999
        mon_dict["cleC"] = 88.8
        mon_dict["cleD"] = True
        print "type(mon_dict) : ", type(mon_dict), " , valeur de mon_dict : ", mon_dict
        mon_dict_value = convert.to_vlevalue(mon_dict)
        print "type(mon_dict_value) : ", type(mon_dict_value)

        print ""
        mon_list = list()
        mon_list.append( 678 )
        mon_list.append( "ffff" )
        mon_list.append( 7.4 )
        mon_list.append( False )
        print "type(mon_list) : ", type(mon_list), " , valeur de mon_list : ", mon_list
        mon_list_value = convert.to_vlevalue(mon_list)
        print "type(mon_list_value) : ", type(mon_list_value)

        print ""
        print "********************************************"
        print "Creation des evenements"

        eventA= self.buildEvent("PortA")
        eventB= self.buildEventWithABoolean("PortB", "NomAttributB", mon_bool)
        eventC= self.buildEventWithAInteger("PortC", "NomAttributC", mon_int)
        eventD= self.buildEventWithADouble("PortD", "NomAttributD", mon_float)
        eventE= self.buildEventWithAString("PortE", "NomAttributE", mon_str)

        # !!! mon_dict_value
        eventF= self.buildEvent("PortF")
        #eventF= testDynamics.ExternalEvent("PortF") not ok !!!
        eventF.putAttribute( "NomAttributF", mon_dict_value ) 

        # !!! mon_list_value
        eventG= self.buildEvent("PortG")
        #eventG= testDynamics.ExternalEvent("PortG") not ok !!!
        eventG.putAttribute( "NomAttributG", mon_list_value ) 

        print ""
        print "********************************************"
        print "Ajout des evenements a la liste d'evenements"

        events.append(eventA);
        events.append(eventB);   
        events.append(eventC); 
        events.append(eventD); 
        events.append(eventE);    
        events.append(eventF);    
        events.append(eventG);    

        print ""
        print "********************************************"
        print "Temporaire"
        print "Lecture des 'Values' produites"

        print ""
        valeur_python = convert.to_pyvalue( mon_bool_value )
        print "valeur python de mon_bool_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_int_value )
        print "valeur python de mon_int_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_float_value )
        print "valeur python de mon_float_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print ""
        valeur_python = convert.to_pyvalue( mon_str_value )
        print "valeur python de mon_str_value : ", valeur_python
        print "et son type : ", type(valeur_python)

        print ""
        valeur_python = convert.to_pyvalue( mon_dict_value )
        print "valeur python de mon_dict_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements  1 a 1 : "
        for k,v in valeur_python.iteritems() :
            print "key : ", k, "value : ", v

        print ""
        valeur_python = convert.to_pyvalue( mon_list_value )
        print "valeur python de mon_list_value : ", valeur_python
        print "et son type : ", type(valeur_python)
        print "lecture des elements 1 a 1 : "
        for e in valeur_python :
            print e

        print ""
        print "********************************************"

        print ""
        print "fin MyModel.output"
        print "--------------------------------------------"
        print ""
	

    def init(self, time): 
        if time == 0.0:
            return 1.0
        else :
            return testDynamics.infinity

    def externalTransition(self, time, events):

        # !!! lecture d'evenements dans events (external events)
        # (to_pyvalue...)

        print ""
        print "--------------------------------------------"
        print "debut MyModel.ExternalTransition"
        print ""
        print "events : ", events
        print "type(events) : ", type(events)
        for event in events :
            print ""
            print "event dont nom du Port :" , event.getPortName()
            if event.haveAttributes() :
                map_attributes_value = event.getAttributes()
                map_attributes = convert.to_pyvalue(map_attributes_value)
                print "type( map_attributes_value) : ", type( map_attributes_value)
                print "type( map_attributes) : ", type( map_attributes)
                print "contenu de event : ", map_attributes
                for k,v in map_attributes.iteritems() :
                    print "attribut de nom : ", k, " ; et de valeur : ", v
            else :
                print "port sans attribut"

        print "********************************************"
        print "********************************************"
        print "********************************************"

        print ""
        print "fin MyModel.ExternalTransition"
        print "--------------------------------------------"
        print ""

###############################################################################
## sans init_events
#    
#    print ""
#    print "Initialisation du Modele..."
#    modelinit = testDynamics.DynamicsInit()
#    my_model = MyModel( modelinit )
#    
#    print ""
#    print "Creation de la liste d'evenements externes..."
#    external_events = testDynamics.ExternalEventList()
#    
#    print ""
#    print "Appels de methodes du Modele :"
#    time = 0.0
#    my_model.init( time )
#    my_model.output(0.0, external_events)
#    my_model.externalTransition( time, external_events )
#    
###############################################################################
## avec init_events

modelinit = testDynamics.DynamicsInit()

print "Creation de la liste d'evenements init..."
init_event_dict = dict()
init_event_dict["parameterA"] = "texte du parametre A"
init_event_dict["parameterB"] = 41
#init_event_dict["parameterC"] = map, set... !!!!!!!!!!!!!!!!!!!!!!
init_event_dict["parameterD"] = False
init_events = convert.to_vlevalue(init_event_dict)
print "type(init_events) : ", type(init_events)

# avec %pythoncode %{ class InitEventList(Map) : pass %}
init_events = testDynamics.InitEventList( init_events ) # Map --> InitEventList

my_model = MyModel( modelinit, init_events )

print ""
print "Creation de la liste d'evenements externes..."
external_events = testDynamics.ExternalEventList()

print ""
print "Appels de methodes du Modele :"
time = 0.0
my_model.init( time )
my_model.output(0.0, external_events)
my_model.externalTransition( time, external_events )

###############################################################################

