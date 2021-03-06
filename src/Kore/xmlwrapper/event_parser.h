/*
 * Copyright (C) 2001-2002 Peter J Jones (pjones@pmade.org)
 * All Rights Reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/** @file
 * This file contains the definition of the xml::event_parser class.
**/

#ifndef __xmlwrapp_event_parser_h__
#define __xmlwrapp_event_parser_h__
#ifdef KAPSUL_EXPORT
	#define KAPSUL_DESC __declspec(dllexport)
#else
	#define KAPSUL_DESC __declspec(dllimport)
#endif

// standard includes
#include <string>
#include <iosfwd>
#include <map>

//namespace xml {
    struct epimpl; // forward declaration of private implementation

/**
 * The xml::event_parser is used to parse an XML document by calling member
 * functions when certain things in the XML document are parsed. In order to
 * use this class you derive a sub-class from it and override the protected
 * virtual functions.
**/
class KAPSUL_DESC event_parser {
public:
    typedef std::map<std::string, std::string> attrs_type;  ///< a type for holding XML node attributes
    typedef size_t size_type;			    ///< size type

    //####################################################################
    /** 
     * xml::event_parser class constructor.
     *
     * @author Peter Jones
    **/
    //####################################################################
    event_parser (void);

    //####################################################################
    /** 
     * xml::event_parser class destructor.
     *
     * @author Peter Jones
    **/
    //####################################################################
    virtual ~event_parser (void);

    //####################################################################
    /** 
     * Call this member function to parse the given file.
     *
     * @param filename The name of the file to parse.
     * @return True if the file was successfully parsed; false otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool parse_file (const char *filename);

    //####################################################################
    /** 
     * Parse what ever data that can be read from the given stream.
     *
     * @param stream The stream to read data from.
     * @return True if the stream was successfully parsed; false otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool parse_stream (std::istream &stream);

    //####################################################################
    /** 
     * Call this function to parse a chunk of xml data. When you are done
     * feeding the parser chucks of data you need to call the parse_finish
     * member function.
     *
     * @param chunk The xml data chuck to parse.
     * @param length The size of the given data chunk
     * @return True if the chunk was parsed sucessfully; false otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool parse_chunk (const char *chunk, size_type length);

    //####################################################################
    /** 
     * Finish parsing chunked data. You only need to call this member
     * function is you were parsing chunked xml data via the parse_chunk
     * member function.
     *
     * @return True if all parsing was successful; false otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool parse_finish (void);

protected:
    //####################################################################
    /** 
     * Override this member function to receive the start_element message.
     * This member function is called when the parser encounters an xml
     * element.
     *
     * @param name The name of the element
     * @param attrs The element's attributes
     * @return You should return true to continue parsing; false to stop.
     * @author Peter Jones
    **/
    //####################################################################
    virtual bool start_element (const char *name, const attrs_type &attrs) = 0;
    
    //####################################################################
    /** 
     * Override this member function to receive the end_element message.
     * This member function is called when the parser encounters the closing
     * of an element.
     *
     * @param name The name of the element that was closed.
     * @return You should return true to continue parsing; false to stop.
     * @author Peter Jones
    **/
    //####################################################################
    virtual bool end_element (const char *name) = 0;

    //####################################################################
    /** 
     * Overried this member function to receive the text message. This
     * member function is called when the parser encounters text nodes.
     *
     * @param contents The contents of the text node.
     * @return You should return true to continue parsing; false to stop.
     * @author Peter Jones
    **/
    //####################################################################
    virtual bool text (const std::string &contents) = 0;

private:
    friend struct epimpl;
    epimpl *pimpl_; // private implementation

    /*
     * Don't allow anyone to copy construct an event_parser or to call the
     * assignment operator. It does not make sense to copy a parser if it is
     * half way done parsing. Plus, it would be a pain!
     */
    event_parser(const event_parser&);
    event_parser& operator= (const event_parser&);
}; // end xml::event_parser class

//} // end xml namespace
#endif
