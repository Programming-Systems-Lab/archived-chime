/*    
 *
 * Copyright (c) 2001: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */

package psl.chime.frax.protocols.bscw;
import HTTPClient.*;
import java.net.*;
import java.io.*;
import psl.chime.frax.protocols.*;
import psl.chime.frax.plugs.PlugStarter;
import psl.chime.sienautils.*;

public class BSCWProtocol extends FRAXProtocol {

    SienaObject siena_obj;
    public static final String PROTOCOL_NAME = "BSCW";
    public String URLString = "";
    private String final_str;
    private DataInputStream returnedInputStream;
    HTTPResponse rsp;
    URI dest;
    public String metaData;


    /**
     * make an internal representation of the
     * object so we can use it when processObject is called
     */
    public BSCWProtocol(SienaObject s) {
	this.siena_obj = s;
	this.URLString = s.getAddress();
	makeURIObj(URLString);
    }


    /**
     * Helper method for making a URI object
     */
    private URI makeURIObj(String object) {
	try {
	    dest = new URI(object);
	} catch (Exception e) {
	    dest = null;
	}
	return dest;
    }


    /**
     * gets an HTTPResponse object when it tries to
     * to make a request to a particular URI
     */
    private HTTPResponse getStream(URI dest) {

	try {
	    System.out.println("*******The destination is: " + dest.getPath());


	    if (dest == null)
		return null;

	    HTTPConnection con = new HTTPConnection(dest.toURL());
	    con.setAllowUserInteraction(false);  //will allow UI for demo
	    //if (siena_obj.getRealm() != null)
		//con.addBasicAuthorization(siena_obj.getRealm(), siena_obj.getUsername(), siena_obj.getPassword());
		if (siena_obj.getUsername() != null && siena_obj.getPassword() != null) {
			try {
				con.addDefaultBasicAuthorization(siena_obj.getUsername(), siena_obj.getPassword());
			} catch (Exception e) {
				//this just means that the authorization has been already added
			}

		}

	    rsp = con.Get(dest.getPath());
	    NVPair[] test = con.getDefaultHeaders();

	    for (int i = 0; i < test.length; i++) {
		System.out.println(test[i].toString());
	    }

	    if (rsp.getStatusCode() >= 300 && rsp.getStatusCode() < 400) {
		System.err.println("Received Error: "+rsp.getReasonLine());
		System.err.println(new String(rsp.getData()));
		return null;
	    } else {
		returnedInputStream = new DataInputStream(rsp.getInputStream());
		return rsp;
	    }

	} catch (IOException ioe) {
	    System.err.println(ioe.toString());
	    return null;
	}
	catch (ModuleException me) {
	    System.err.println("Error handling request: " + me.getMessage());
	    return null;
	}
    }

    /**
     * Special BSCW thing
     * Allows you to get the XML out of the pages
     */
    private HTTPResponse makeJget(URI tourl) {
	try {
	    URI newdest = new URI("http", tourl.getHost(), tourl.getPort(), tourl.getPath() + "?op=jget");

	return getStream(newdest);
	} catch (Exception e) {
	    return null;
	}
    }




    /**
     * Needed for this system to work
     * this method gets called from the class loader once
     * the constructor has been loaded and the class loaded
     */
    public boolean processObject() {

	HTTPResponse rsp;
	HTTPResponse rsp2;

	//try the URL as specified
	if (!dest.getPath().trim().endsWith("/")) {
	    try {
		rsp = getStream(new URI(URLString));
	    } catch (Exception e) {
		System.err.println(e.getMessage());
		rsp = null;
	    }

	    if (rsp == null)
		return false;

	    try {
		rsp = makeJget(rsp.getEffectiveURI());
	    } catch (Exception e) {
		System.err.println(e.getMessage());
		return false;
	    }


	} else {
	    rsp = makeJget(dest);
	}


	if (rsp == null)
	    return false;

	else {

	    Long length;
	    try {
		length = new Long(getField(rsp, "Content-Length"));
	    } catch (NumberFormatException e) {
		System.err.println("The length can't be cast");
		length = new Long(-1);

	    }

	    try {
		String returning = rsp.getEffectiveURI().toString();

		goPlug(PROTOCOL_NAME, returning, makeParams(siena_obj, "", returnedInputStream, length));
		return true;

		//maybe the getEffective URI method will fail so have a backup
	    } catch (Exception e) {

		String returning = rsp.getOriginalURI().toString();


		goPlug(PROTOCOL_NAME, returning, makeParams(siena_obj, "", returnedInputStream, length));
		return true;
	    }
	}

    }



    /**
     * Helper method to find out a particular field of a
     * certain HttpResponse
     */
    private String getField(HTTPResponse rsp, String name) {
	try {
	    return rsp.getHeader(name);
	} catch (Exception e) {
	    return "";
	}
    }

    /**
     * Test to see if the class loads and runs correctly
     */
    public static void main(String args[]) {
	/*
	  BSCWProtocol bs = new BSCWProtocol("http://mercer.psl.cs.columbia.edu/bscw/bscw.cgi");
	  bs.processObject();
	  System.exit(0);
	*/
    }
}

