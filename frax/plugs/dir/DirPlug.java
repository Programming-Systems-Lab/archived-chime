 /*    
 * Copyright (c) 2001: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */

package psl.chime.frax.plugs.dir;

import psl.chime.frax.plugs.FRAXPlug;
import java.lang.*;
import java.io.*;
import psl.chime.sienautils.*;

public class DirPlug extends FRAXPlug {

    public String final_XML;
    public SienaObject siena_obj;

    /**
     * Dir Plug just takes the xml given to it from the protocol
     * and wraps XML
     */
    public DirPlug(String toAdd, DataInputStream ds, Long length, SienaObject s) {
	siena_obj = s;
	final_XML =  "<?xml version=\"1.0\"?>\n<MetaInfo createDate=\'" + System.currentTimeMillis() + "\' type = \'dir\'>\n" + toAdd + "</MetaInfo>\n\n";
    }

    /**
     * returns the XML describing the metadata
     */
    public String toXML() {
	return final_XML;
    }
}

