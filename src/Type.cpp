/***************************************************************************
*   Copyright (C) 2008 by Daniel Wendt                                    *
*   gentoo.murray@gmail.com                                               *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/
#include <string>
#include <map>
#include "./Class.h"
#include "./Type.h"
#include <boost/lexical_cast.hpp>

namespace osm2pgr {

Type::Type(int64_t id, std::string name) :
  m_id(id),
  m_name(name) {
}

Type::~Type() {
}

void Type::AddClass(const Class &pClass) {
   m_Classes[pClass.name()] = pClass;
}


Type::Type(const char **atts) {
    auto **attribut = atts;
    while (*attribut != NULL) {
        const char* name = *attribut++;
        const char* value = *attribut++;
        if (strcmp(name, "id") == 0) {
            m_id = boost::lexical_cast<int64_t>(value);
        } else if (strcmp(name, "name") == 0) {
            m_name = value;
        } else {
            auto tag_key = boost::lexical_cast<std::string>(name);
            auto tag_value = boost::lexical_cast<std::string>(value);
            m_tags[tag_key] = tag_value;
        }
    }
}

void
Type::add_class(const char **atts) {
    AddClass(Class(atts));
}


}  // end namespace osm2pgr
