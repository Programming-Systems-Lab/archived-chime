/*    
 *
 * Copyright (c) 2002: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */

package psl.chime.frax.protocols.lfs;

import java.lang.*;
import java.io.*;
import psl.chime.frax.plugs.*;
import psl.chime.frax.protocols.*;
import psl.chime.sienautils.*;

public class LFSProtocol extends FRAXProtocol {

    File path;
    String PROTOCOL_NAME = "LFS";
    SienaObject siena_obj;

    /**
     * A constructor which is called by the class loader
     * loads some internal data
     */
    public LFSProtocol(SienaObject s) {
	this.siena_obj = s;
	path = new File(siena_obj.getAddress());
	System.err.println("The filename is: " + path.toString());
    }

    /**
     * The method which gets the file from the local disk
     * and makes a dataInputStream out of it
     */
    public boolean processObject() {

	System.out.println("starting LFS process Object - path is: " + path);

	if (path.exists()) {

	    //if it is just a file call the plug
	    if (path.isFile()) {

		try {
		    int file_length = (int) path.length();
		    //byte[] data = new byte[file_length];
		    FileInputStream fis = new FileInputStream(path);
		    //fis.read(data);

		    Object[] params = makeParams(siena_obj, addToXML(path), new DataInputStream(fis), new Long(path.length()));
		    System.out.println("After making params");
		    goPlug(PROTOCOL_NAME, path.getAbsolutePath(), params);
		    return true;

		} catch (IOException e) {
		    System.err.println("In LFS Protocol:" + e.getMessage());
		}

	    }

	    //if it is a directory let's get some info
	    else if (path.isDirectory()) {
		System.out.println("This is a directory");
		File[] directory = path.listFiles();

		String final_xml = addToXML(path) + generateFileList(path);
		//formAttrAboutEachFile(directory);
		Object[] params = makeParams(siena_obj, final_xml, null, new Long(0));
		goPlug(PROTOCOL_NAME, path.getAbsolutePath() + File.separatorChar, params);
		return true;
	    }
	}
	System.out.println("Error accessing path: " + path.toString());
	return false;
    }




    public String formAttrAboutEachFile(File[] directory) {
	String final_xml = "";



	for (int i = 0; i < directory.length; i++) {
	    final_xml = final_xml + addToXML(directory[i]);
	}

	return final_xml;
}


    /**
     * Create the XML given a file
     */
    public String addToXML(File file) {
	String file_info = "<Protocol>" + PROTOCOL_NAME + "</Protocol>\n";
	file_info = file_info + "<Name>" + file.getAbsolutePath() + "</Name>\n";
	if (file.isFile())
	    file_info = file_info + "<Type>FILE</Type>\n";
	else
	    file_info = file_info + "<Type>DIRECTORY</Type>\n";
	file_info = file_info + "<Last-Modified>" + file.lastModified() + "</Last-Modified>\n";
	file_info = file_info + "<Hidden>" + file.isHidden() + "</Hidden>\n";
	file_info = file_info + "<Size>" + file.length() + "</Size>\n";
	return file_info;
    }



    /**
     * Helper method - generate a file list if this is a directory
     * only called when dealing with directories
     */
    private String generateFileList(File file) {
	File[] list = file.listFiles();
	String temp = "\n<LIST-FILES>\n";
	for (int i = 0; i < list.length; i++) {
	    temp = temp + "<FILE>\"" + addToXML(list[i]) + "\"</FILE>";
	    temp = temp + "\n\n";
	}
	temp = temp + "</LIST-FILES>\n";
	return temp;
    }

    /**
     * a routine to test the functionality of the class
     */
    public static void main(String args[]) {
	//LFSProtocol lf = new LFSProtocol("/home/sparky/FRAX/TestDir/");
	//lf.processObject();
    }
}
