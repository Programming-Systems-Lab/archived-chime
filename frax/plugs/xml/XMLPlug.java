/*    
 *
 * Copyright (c) 2002: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */

package psl.chime.frax.plugs.xml;

import psl.chime.frax.plugs.FRAXPlug;
import java.lang.*;
import java.io.*;
import psl.chime.sienautils.*;

public class XMLPlug extends FRAXPlug {

    public String final_XML = "";
    BufferedReader br;
    SienaObject siena_obj;

    /**
     * constructor which creates an internal representation
     * of the object
     */
    public XMLPlug(String toAdd, DataInputStream ds, Long length, SienaObject s) {
	siena_obj = s;
	br = new BufferedReader(new InputStreamReader(ds));

    }


    /**
     * Since this is already XML - just return it with the info
     * which the protocol was able to obtain
     */
    public String toXML() {
	try {
	    String temp;
	    while((temp = br.readLine()) != null) {
		final_XML = final_XML + temp + "\n";
		System.err.println("Reading XML file");
	    }

	} catch (IOException e) {
	    System.err.println("An IOException has been thrown");
	}

	return final_XML;
    }
}

