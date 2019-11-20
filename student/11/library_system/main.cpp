/*
 * Joonas Kakkuri
 * 274166
 * joonas.kakkuri@tuni.fi
 *
 * Main.cpp
 * --------
 * Creates the library object, uses the file_reader module to init the obj and
 * starts the cli module.
 *
 * Library.cpp
 * -----------
 * Library object is responsible of handling function calls and data structure
 *
 * TIE-0220x S2019
 * */
#include "file_reader.hh"
#include "cli.hh"
#include <iostream>

using namespace std;

int main()
{

    std::shared_ptr<Library> lib = std::make_shared<Library>();
    // If we can't read the files, return error.
    if ( !read_file_to_lib(lib) ){
        return EXIT_FAILURE;
    }
    // Otherwise, start the cli.
    Cli cli(lib);
    while( cli.exec_prompt() ){}
    return EXIT_SUCCESS;
}
