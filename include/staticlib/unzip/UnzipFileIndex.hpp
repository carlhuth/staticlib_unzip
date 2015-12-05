/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   UnzipFileIndex.hpp
 * Author: alex
 *
 * Created on October 8, 2015, 6:58 PM
 */

#ifndef STATICLIB_UNZIP_UNZIPFILEINDEX_HPP
#define	STATICLIB_UNZIP_UNZIPFILEINDEX_HPP

#include <string>
#include <utility>
#include <cstdint>

#ifdef STATICLIB_WITH_ICU
#include <unicode/unistr.h>
#endif // STATICLIB_WITH_ICU

#include "staticlib/pimpl.hpp"


namespace staticlib {
namespace unzip {

/**
 * Represents ZIP file entry
 */
struct FileEntry {
    /**
     * Entry data offset from the start of the file
     */
    int32_t offset = -1;
    /**
     * Compressed length
     */
    int32_t comp_length = -1;
    /**
     * Uncompressed length
     */
    int32_t uncomp_length = -1;
    /**
     * Compression method
     */
    uint16_t comp_method = 0;

    /**
     * Constructor, constructs an empty entry
     */
    FileEntry() { }
    
    /**
     * Constructor
     * 
     * @param offset entry data offset from the start of the file
     * @param comp_length compressed length
     * @param uncomp_length uncompressed length
     * @param comp_method compression method
     */
    FileEntry(int32_t offset, int32_t comp_length, int32_t uncomp_length, uint16_t comp_method) :
    offset(offset),
    comp_length(comp_length),
    uncomp_length(uncomp_length),
    comp_method(comp_method) { }
    
    /**
     * Returns true if this instance represents an empty (invalid) entry
     * 
     * @return true if this instance represents an empty (invalid) entry, false otherwise
     */
    bool is_empty() {
        return -1 == offset;
    }
};

/**
 * Represents an index over the entries inside the ZIP file
 */
class UnzipFileIndex : public staticlib::pimpl::PimplObject {
protected:
    /**
     * Implementation class
     */
    class Impl;
public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(UnzipFileIndex)
            
    /**
     * Constructor
     * 
     * @param zip_file_path path to the ZIP file
     */
#ifdef STATICLIB_WITH_ICU
    UnzipFileIndex(icu::UnicodeString zip_file_path);
#else
    UnzipFileIndex(std::string zip_file_path);
#endif // STATICLIB_WITH_ICU
    
    /**
     * Returns the ZIP entry with the specified name
     * 
     * @param name name of ZIP entry
     * @return ZIP entry with the specified name, empty entry if not found
     */
#ifdef STATICLIB_WITH_ICU
    FileEntry find_zip_entry(const icu::UnicodeString& name) const;
#else
    FileEntry find_zip_entry(const std::string& name) const;
#endif // STATICLIB_WITH_ICU
    
    /**
     * Returns a path to the ZIP file
     * 
     * @return a path to the ZIP file
     */
    const std::string& get_zip_file_path() const;
    
#ifdef STATICLIB_WITH_ICU
    /**
     * Returns a unicode path to the ZIP file
     * 
     * @return a unicode path to the ZIP file
     */
    const icu::UnicodeString& get_zip_file_upath() const;
#endif    
};

} // namespace
}

#endif	/* STATICLIB_UNZIP_UNZIPFILEINDEX_HPP */
