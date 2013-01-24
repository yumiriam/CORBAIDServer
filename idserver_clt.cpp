// idserver_clt.cc - This is the code based on the source code of example 2 used
//              in Chapter 2 "The Basics" of the omniORB user guide.
//
//              This is the client. The object reference is given as a
//              stringified IOR on the command line.
//
// Usage: idserver_clt <object reference>
//
// Obs.: You MUST set your environment before running the program
//       export OMNIORB_CONFIG=/etc/omniORB.cfg

#include "idserver.hh"

#ifdef HAVE_STD
#  include <iostream>
#  include <fstream>
   using namespace std;
#else
#  include <iostream.h>
#endif

static CORBA::Object_ptr getObjectReference(CORBA::ORB_ptr orb);

static void hello(MiLissa::IdServer_ptr e)
{
  CORBA::String_var src = (const char*) "Connecting";

  CORBA::String_var dest = e->generateId(src);

  cout << "I said, \"" << (char*)src << "\"." << endl
       << "The IdServer object replied, \"" << (char*)dest <<"\"." << endl;
}

//////////////////////////////////////////////////////////////////////

/*
int main(int argc, char** argv)
{


  try {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    if( argc != 2 ) {
      cerr << "usage:  idserver_clt <object reference>" << endl;
      return 1;
    }

    CORBA::Object_var obj = orb->string_to_object(argv[1]);
    MiLissa::IdServer_var serverref = MiLissa::IdServer::_narrow(obj);
    if( CORBA::is_nil(serverref) ) {
      cerr << "Can't narrow reference to type IdServer (or it was nil)." << endl;
      return 1;
    }
    for (CORBA::ULong count=0; count<10; count++) 
      hello(serverref);

    orb->destroy();
  }
  catch(CORBA::TRANSIENT&) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  }
  catch(CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name() << endl;
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
*/

int main (int argc, char **argv)  {
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    CORBA::Object_var obj = getObjectReference(orb);

    MiLissa::IdServer_var serverref = MiLissa::IdServer::_narrow(obj);

    //for (CORBA::ULong count=0; count < 10; count++)
      hello(serverref);

    orb->destroy();
  } catch(CORBA::TRANSIENT&) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  } catch(CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name() << endl;
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

//////////////////////////////////////////////////////////////////////

static CORBA::Object_ptr getObjectReference(CORBA::ORB_ptr orb) {
  CosNaming::NamingContext_var rootContext;
  
  try {
    // Obtain a reference to the root context of the Name service:
    CORBA::Object_var obj;
    obj = orb->resolve_initial_references("NameService");

    // Narrow the reference returned.
    rootContext = CosNaming::NamingContext::_narrow(obj);
    if( CORBA::is_nil(rootContext) ) {
      cerr << "Failed to narrow the root naming context." << endl;
      return CORBA::Object::_nil();
    }
  } catch (CORBA::NO_RESOURCES&) {
    cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
	 << "with the location" << endl
	 << "of the naming service." << endl;
    return 0;
  } catch(CORBA::ORB::InvalidName& ex) {
    // This should not happen!
    cerr << "Service required is invalid [does not exist]." << endl;
    return CORBA::Object::_nil();
  }

  // Create a name object, containing the name test/context:
  CosNaming::Name name;
  name.length(2);

  name[0].id   = (const char*) "test";       // string copied
  name[0].kind = (const char*) "my_context"; // string copied
  name[1].id   = (const char*) "IdServer";
  name[1].kind = (const char*) "Object";
  // Note on kind: The kind field is used to indicate the type
  // of the object. This is to avoid conventions such as that used
  // by files (name.type -- e.g. test.ps = postscript etc.)

  try {
    // Resolve the name to an object reference.
    return rootContext->resolve(name);
  } catch(CosNaming::NamingContext::NotFound& ex) {
    // This exception is thrown if any of the components of the
    // path [contexts or the object] aren't found:
    cerr << "Context not found." << endl;
  } catch(CORBA::TRANSIENT& ex) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "naming service." << endl
	 << "Make sure the naming server is running and that omniORB is "
	 << "configured correctly." << endl;

  } catch(CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name()
	 << " while using the naming service." << endl;
    return 0;
  }

  return CORBA::Object::_nil();
}
