/*
 * This file is part of Manga.
 *
 * Manga is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Manga is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with manga.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INC_ERROR_CODES_H_
#define INC_ERROR_CODES_H_

typedef enum general_errors{
    MAGNA_OK                 = 0,
    MAGNA_FAILED             = -1,
    MAGNA_BUSY               = -2,
    MAGNA_TIMEOUT            = -3,
    MAGNA_NOT_SUPPORTED      = -4,
    MAGNA_NOT_IMPLEMENTED    = -5,
    MAGNA_INVALID_ARGUMENT   = -6,
    MAGNA_QUEUE_FULL         = -7,
    MAGNA_HAL_ERROR         = -8
} manga_error_code_t;

#endif /* INC_ERROR_CODES_H_ */
