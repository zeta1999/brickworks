/*
 * Brickworks
 *
 * Copyright (C) 2022 Orastron Srl unipersonale
 *
 * Brickworks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Brickworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *
 * File author: Stefano D'Angelo
 */

/*!
 *  module_type {{{ foundation }}}
 *  version {{{ 0.1.0 }}}
 *  requires {{{ bw_config }}}
 *  description {{{
 *    A common header to make sure that a bunch of basic definitions are
 *    available and consistent for all Brickworks modules.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>0.1.0</strong>:
 *        <ul>
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef _BW_COMMON_H
#define _BW_COMMON_H

/*! api {{{
 *    #### bw_config
 *    At its very beginning, this header `#include`s `<bw_config.h>`, which is
 *    a file you can use to supply custom `#include`s and `#define`s that
 *    override defaults (see [bw_config](bw_config)).
 *
 *    Alternatively, your compiler probably allows you to specify definitions on
 *    the command line.
 *  >>> */
#include <bw_config.h>

/*! ...
 *    #### NULL
 *    If `NULL` is not defined, then `stddef.h` is `#include`d.
 *  >>> */
#ifndef NULL
# include <stddef.h>
#endif

/*! ...
 *    #### Exact-width integer types
 *    If <code class="hljs">(u)int{8,16,32,64}_t</code>,
 *    `INT{8,16,32,64}_{MIN,MAX}`, and `UINT{8,16,32,64}_MAX` are not defined,
 *    then `stdint.h` is `#include`d (actually, only testing against
 *    `INT32_MAX` but expecting the others to be finally defined).
 *  >>> */
#ifndef INT32_MAX
# include <stdint.h>
#endif

/*! ...
 *    #### INFINITY
 *    If `INFINITY` is not defined, then `math.h` is `#include`d.
 *  >>> */
#ifndef INFINITY
# include <math.h>
#endif

/*! ...
 *    #### BW_MALLOC, BW_REALLOC, BW_FREE
 *    If any of these is not defined, then `stdlib.h` is `#include`d and the
 *    missing ones are defined as `malloc`, `realloc`, or `free`, respectively.
 *  >>> */
#if !defined(BW_MALLOC) || !defined(BW_REALLOC) || !defined(BW_FREE)
# include <stdlib.h>
# ifndef BW_MALLOC
#  define BW_MALLOC malloc
# endif
# ifndef BW_REALLOC
#  define BW_REALLOC realloc
# endif
# ifndef BW_FREE
#  define BW_FREE free
# endif
#endif

/*! ... }}} */

#endif
