/*    
 *
 * Copyright (c) 2001: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */
/**
 * This is the base of all FRAX documents
 *
 * The document has the following format:
 *
 * <FUIMessage>
 *		<action> an action describtion </action>
 * </FUIMessage>
 */

package frax.FRAXUserInterface;

import org.jdom.Document;
import org.jdom.Element;

public class FRAXDoc extends Document{
   public FRAXDoc(){
      super( new Element("FUIMessage")
		  .addContent( new Element("action") ));
   }
}
      
