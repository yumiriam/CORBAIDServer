// idserver_impl.cc - This is code is based on the source code of example 2 used
//               in Chapter 2 "The Basics" of the omniORB user guide.
//
//               This is the object implementation.
//
// Usage: idserver_impl
//
//        Description...
//
// Obs.: You MUST set your environment before running the program
//       export OMNIORB_CONFIG=/etc/omniORB.cfg

#include "idserver.hh"
#include "mongo/client/dbclient.h"


#ifdef HAVE_STD
#  include <iostream>
#  include <cstdlib>
#  include <cstdio>
#  include <cstring>
#  include <ctime>
   using namespace std;
#else
#  include <iostream.h>
#  include <stdlib.h>
#  include <stdio.h>
#  include <string.h>
#  include <time.h>
#endif

static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr, CORBA::Object_ptr);

// Connection with MongoDB
void db_connect(mongo::DBClientConnection* c) {
  (*c).connect("localhost");
}

class IdServer_i : public POA_MiLissa::IdServer,
                   public PortableServer::RefCountServantBase
{
public:
  inline IdServer_i() {}
  virtual ~IdServer_i() {}
  virtual char* generateId(const char* fileName);
  virtual bool verifyId(const char* id);
};

char* IdServer_i::generateId(const char* fileName) {
  try {
    mongo::DBClientConnection conn;
    db_connect(&conn);
    std::cout << "Connected ok" << std::endl;
    
    /* tenta gerar um UID */
	char tmpChUid[255], chUid[255];
    
    bool id_exists = true;
    while (id_exists) {
		/* gerar o UID a partir do nome e da data atual */
		if (strlen(fileName) > 4) {
			strncpy( tmpChUid, fileName, 5 ); // copia 5 primeiros caracteres
		} else {
			strncpy( tmpChUid, fileName, strlen(fileName) );  // copia tudo
		}
		sprintf( chUid, "%s%ld", tmpChUid, time(NULL) );
		
		/* verificar existencia do UID */		
		auto_ptr<mongo::DBClientCursor> cursor =
			conn.query("sdfinal.videos", QUERY("_id" << chUid));
		if ( !(cursor->more()) ) // encontrou algum resultado
			id_exists = false;
    }

	/* criar objeto BSON para insercao no BD */
	mongo::BSONObj video = BSON( "_id" << chUid );
	/* inserir objeto no banco de dados */
	conn.insert("sdfinal.videos", video);
  
  	return CORBA::string_dup(chUid);  
  } catch( const mongo::DBException &e ) {
    std::cout << "Caught " << e.what() << std::endl;
  }

  return CORBA::string_dup(fileName);
}

bool IdServer_i::verifyId(const char* id) {
  CORBA::Boolean result = 1;
  
  try {

    mongo::DBClientConnection conn;
    db_connect(&conn);
    std::cout << "Connected ok" << std::endl;
    
	/* verificar existencia do UID */		
	auto_ptr<mongo::DBClientCursor> cursor =
		conn.query("sdfinal.videos", QUERY("_id" << id));
	if ( !(cursor->more()) ) // encontrou algum resultado
		result = 0;
	 
  } catch( const mongo::DBException &e ) {
    std::cout << "Caught " << e.what() << std::endl;
  }
  
  return result;
}

//////////////////////////////////////////////////////////////////////
/*
int main(int argc, char** argv) {
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    IdServer_i* myserver = new IdServer_i();
      
    PortableServer::ObjectId_var myserverid = poa->activate_object(myserver);

    // Obtain a reference to the object, and print it out as a
    // stringified IOR.
    obj = myserver->_this();
    CORBA::String_var sior(orb->object_to_string(obj));
    cout << (char*)sior << endl;

    myserver->_remove_ref();

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    orb->run();
  } catch(CORBA::SystemException& ex) {
    cerr << "Caught CORBA::" << ex._name() << endl;
  } catch(CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  } catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }
  return 0;
}
*/

int main(int argc, char **argv) {
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    IdServer_i* myserver = new IdServer_i();

    PortableServer::ObjectId_var myserverid = poa->activate_object(myserver);

    // Obtain a reference to the object, and register it in
    // the naming service.
    obj = myserver->_this();

    CORBA::String_var x;
    x = orb->object_to_string(obj);
    cout << x << endl;

    if( !bindObjectToName(orb, obj) )
      return 1;

    myserver->_remove_ref();

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    orb->run();
  }
  catch(CORBA::SystemException& ex) {
    cerr << "Caught CORBA::" << ex._name() << endl;
  }
  catch(CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////

static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref) {
  CosNaming::NamingContext_var rootContext;

  try {
    // Obtain a reference to the root context of the Name service:
    CORBA::Object_var obj;
    obj = orb->resolve_initial_references("NameService");

    // Narrow the reference returned.
    rootContext = CosNaming::NamingContext::_narrow(obj);
    if( CORBA::is_nil(rootContext) ) {
      cerr << "Failed to narrow the root naming context." << endl;
      return 0;
    }
  } catch (CORBA::NO_RESOURCES&) {
    cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
	 << "with the location" << endl
	 << "of the naming service." << endl;
    return 0;
  } catch (CORBA::ORB::InvalidName&) {
    // This should not happen!
    cerr << "Service required is invalid [does not exist]." << endl;
    return 0;
  }

  try {
    // Bind a context called "test" to the root context:

    CosNaming::Name contextName;
    contextName.length(1);
    contextName[0].id   = (const char*) "test";       // string copied
    contextName[0].kind = (const char*) "my_context"; // string copied
    // Note on kind: The kind field is used to indicate the type
    // of the object. This is to avoid conventions such as that used
    // by files (name.type -- e.g. test.ps = postscript etc.)

    CosNaming::NamingContext_var testContext;
    try {
      // Bind the context to root.
      testContext = rootContext->bind_new_context(contextName);
    } catch(CosNaming::NamingContext::AlreadyBound& ex) {
      // If the context already exists, this exception will be raised.
      // In this case, just resolve the name and assign testContext
      // to the object returned:
      CORBA::Object_var obj;
      obj = rootContext->resolve(contextName);
      testContext = CosNaming::NamingContext::_narrow(obj);
      if( CORBA::is_nil(testContext) ) {
        cerr << "Failed to narrow naming context." << endl;
        return 0;
      }
    }

    // Bind objref with name IdServer to the testContext:
    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = (const char*) "IdServer";   // string copied
    objectName[0].kind = (const char*) "Object"; // string copied

    try {
      testContext->bind(objectName, objref);
    } catch(CosNaming::NamingContext::AlreadyBound& ex) {
      testContext->rebind(objectName, objref);
    }
    // Note: Using rebind() will overwrite any Object previously bound
    //       to /test/IdServer with obj.
    //       Alternatively, bind() can be used, which will raise a
    //       CosNaming::NamingContext::AlreadyBound exception if the name
    //       supplied is already bound to an object.

    // Amendment: When using OrbixNames, it is necessary to first try bind
    // and then rebind, as rebind on it's own will throw a NotFoundexception if
    // the Name has not already been bound. [This is incorrect behaviour -
    // it should just bind].
  } catch(CORBA::TRANSIENT& ex) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "naming service." << endl
	 << "Make sure the naming server is running and that omniORB is "
	 << "configured correctly." << endl;

    return 0;
  } catch(CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name()
	 << " while using the naming service." << endl;
    return 0;
  }
  return 1;
}
