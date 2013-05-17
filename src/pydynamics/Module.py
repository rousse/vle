import testDynamics

class MyModel(testDynamics.Dynamics):
    
    def output(self,time,events):
        #MySet = testDynamics.Set()
	MyMap = testDynamics.Map.create()
        MySet = testDynamics.Set.create()
        MyDouble = self.buildDouble(2.0)
        MyInteger = self.buildInteger(1)
        MyBoolean = self.buildBoolean(True)
        MyString = self.buildString("String")
        print "********************************************"
	print "Type de MyMap :", type(MyMap)
        print "Type de MyDouble :", type(MyDouble)
        print "********************************************"
        MyMap.addBoolean("Bool1", MyBoolean)
        print "MyMap Boolean 1 :", MyMap.getBoolean("Bool1")
        MyMap.addBoolean("Bool2", False)
        print "MyMap Boolean 2 :", MyMap.getBoolean("Bool2")

        MyMap.addDouble("Double", 2.0)
        print "MyMap Double :",MyMap.getDouble("Double")
        MyMap.addInt("Int", 1)
        print "MyMap Integer :",MyMap.getInt("Int")
        MyMap.addString("Str", "value")
        print "MyMap String :",MyMap.getString("Str")
        MyMap.addMap("Map")
        print "MyMap Map :",MyMap.getMap("Map")
        #MyMap.addSet("Set")
        #print "MyMap Set :",MyMap.getSet("Set")

        #print type(MyInteger)	       
        #print dir(testDynamics)	
        #print "********************************************"
        #print "Test des Value (Double,String,Integer,Boolean)"
        #test = MyDouble.isDouble()
        #print "MyDouble est un double :",test
        #test = MyDouble.isInteger()
        #print "MyDouble est un integer :",test
        #test = MyInteger.isInteger()
        #print "MyInteger est un integer :",test
        #test = MyBoolean.isBoolean()
        #print "MyBoolean est un boolean :",test
        #test = MyString.isString()
        #print "MyString est un string :",test
        #print "********************************************"
        #print "Creation des evenements"
        #eventA= self.buildEvent("PortA")
        #eventB= self.buildEventWithAInteger("PortB", "NomAttributB", 1) 
        #eventC= self.buildEventWithADouble("PortC", "NomAttributC", 2.2)
        #eventD= self.buildEventWithABoolean("PortD", "NomAttributD", False)  
        #eventE= self.buildEventWithAString("PortE", "NomAttributE", "value") 
        #print "********************************************"

        #print "Ajout des evenements a la liste d'evenements"
	#events.append(eventA);
        #events.append(eventB);   
	#events.append(eventC); 
	#events.append(eventD); 
	#events.append(eventE);    
	

    def init(self, time): 
        if time == 0.0:
            return 1.0
        else :
            return testDynamics.infinity

    def externalTransition(self, time, events):
        print "********************************************"
        print "Test des noms de port"
        print "Le nom du Port de eventA :",events[0].getPortName()
        print "Le nom du Port de eventB :",events[1].getPortName()
        print "Le nom du Port de eventC :",events[2].getPortName()
        print "Le nom du Port de eventD :",events[3].getPortName()
        print "Le nom du Port de eventE :",events[4].getPortName()
        print "********************************************"
        print "Test la presence d'un attribut"
        print "Presence d'un attribut pour eventA :",events[0].haveAttributes()
        print "Presence d'un attribut pour eventB :",events[1].haveAttributes()
        print "********************************************"
        print "Affichage de l'attribut"
        print "Attribut pour eventB :",events[1].getIntegerAttributeValue("NomAttributB")
        print "Attribut pour eventC :",events[2].getDoubleAttributeValue("NomAttributC")
        print "Attribut pour eventD :",events[3].getBooleanAttributeValue("NomAttributD")
        print "Attribut pour eventE :",events[4].getStringAttributeValue("NomAttributE")

print "Initialisation du Modele..."
modelinit = testDynamics.DynamicsInit()
a = MyModel(modelinit)
print "Creation de la liste d'evenements..."
lst = testDynamics.ExternalEventList()
assert(a.init(0.0) == 1.0)
a.output(0.0, lst)
#a.externalTransition(0.0,lst)
#print dir(eventB)
#print type(events)
