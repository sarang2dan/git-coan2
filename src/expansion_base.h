#ifndef EXPANSION_BASE_H
#define EXPANSION_BASE_H
#pragma once
/***************************************************************************
 *   Copyright (C) 2007-2013 Mike Kinghan, imk@burroingroingjoing.com      *
 *   All rights reserved.                                                  *
 *                                                                         *
 *   Contributed originally by Mike Kinghan, imk@burroingroingjoing.com    *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *                                                                         *
 *   Redistributions of source code must retain the above copyright        *
 *   notice, this list of conditions and the following disclaimer.         *
 *                                                                         *
 *   Redistributions in binary form must reproduce the above copyright     *
 *   notice, this list of conditions and the following disclaimer in the   *
 *   documentation and/or other materials provided with the distribution.  *
 *                                                                         *
 *   Neither the name of Mike Kinghan nor the names of its contributors    *
 *   may be used to endorse or promote products derived from this software *
 *   without specific prior written permission.                            *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS    *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,   *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS *
 *   OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED    *
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,*
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF *
 *   THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH  *
 *   DAMAGE.                                                               *
 *                                                                         *
 **************************************************************************/
#include "parse_buffer.h"
#include "reference.h"
#include "chew.h"
#include <string>
#include <vector>
#include <memory>

/*! \file expansion_base.h
    This file defines class `expansion_base`.
*/

/*! \brief Class `expansion_base` is a base for classes that encapsulates
	a mode of macro-expansion of a reference.
*/
struct expansion_base : reference
{
	//! Construct from a reference
	explicit expansion_base(reference const & ref);
	~expansion_base() override = default;

	//! Get the current expanded value of the reference
	std::string const & value() const {
        return _value;
	}

	/*! Perform the expansion of the reference returning the
        total number of edits applied
    */
	virtual unsigned expand() = 0;

	/*! Get a string representing the invocation of the reference
        with the current expansions of its arguments
	*/
	std::string const & invocation() const override {
        static std::string s;
        s = id();
        if (args()) {
            s += args().str();
        }
		return s;
	}

	static std::unique_ptr<expansion_base>
	factory(bool explain, reference const & ref);

protected:

	/*! Assign the expand-flags of the reference's arguments, if any,
        in accordance with the definition, if any, of the referenced symbol
    */
	void set_expansion_flags();

	/*! Seek to the next argument of the reference, if any, that is eligible for
        returning its index if found, else `args.size()`
	*/
	size_t seek_expandable_arg() {
		for (	;_cur_arg < args().size() && !args().is_expandable(_cur_arg);
			++_cur_arg){}
		return _cur_arg;
	}

	/*! Edit a `parse_buffer`
		\param str	The string to edit
		\param at	Offset in `str` where replacement starts
		\param len	Length to be replaced.
		\param replacement String to replace the `len` characters
			at `at`
	*/
	void edit(	std::string & str,
					size_t at, size_t len,
					std::string const & replacement) {
        str.replace(at,len,replacement);
	}


	/*! Replace all remaining occurrences of a reference throughout a parse
		buffer
		\param str The string to edit.
		\param e An expansion, s.t. that each ocurrence of that expansion's
            reference in `str` is to replaced with its expanded value.
		\param	off Offset into `str` at which to start replacement.
		\return The number of replacements made.
	*/
	unsigned edit_buf(
		std::string & str,
		expansion_base const & e,
		size_t off = 0);

	/*! Replace all occurrences of a reference in a terminal segment of
		the `subst_args`.

		\param e An expansion, s.t. that each ocurrence of that expansion's
            reference in `pb` is to replaced with its expanded value.
        \param replacement A string that is to replace occurrences of 'ref`
		\param start Index of the `subst_args` element at which to start.
		\return The number of replacements made
	*/
	unsigned edit_trailing_args(
		expansion_base const & e,
		size_t start = 0);

	//! Say whether all arguments are fully expanded
	bool args_expansion_done() const {
		return _cur_arg == args().size();
	}

	//! Expand a string, returning the number of edits applied
	virtual unsigned expand(std::string & str) = 0;

	/*! Substitute the fully expanded arguments into the
		definition of the reference, returning true
		if the current value of the expansion is changed.
	*/
	bool substitute();

	//! The current expanded value
	std::string _value;
	//! Index of the first argument not yet fully expanded.
	size_t _cur_arg = 0;
};

#endif // EOF
