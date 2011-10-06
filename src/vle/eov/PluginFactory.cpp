/*
 * @file vle/eov/PluginFactory.cpp
 *
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2007 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2011 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2011 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <vle/eov/PluginFactory.hpp>
#include <vle/utils/Algo.hpp>
#include <vle/utils/Debug.hpp>
#include <vle/utils/Module.hpp>


namespace vle { namespace eov {

PluginPtr PluginFactory::build(oov::PluginPtr oovplugin, NetStreamReader* net)
{
    utils::ModuleCache::iterator module =
        utils::ModuleCache::instance().load(mPlugin, mPath);

    void* symbol = module->get("makeNewEovPlugin");

    if (not symbol) {
        throw utils::ArgError(
            fmt(_("Error when searching `makeNewEovPlugin' function in"
                  " eov plugin `%1%' path `%2%' (%3%)")) % mPlugin % mPath %
            module->path());
    }

    function fct(utils::pointer_to_function < function >(symbol));
    Plugin* call = fct(oovplugin, net);

    if (not call) {
        throw utils::InternalError(fmt(
                _("Error when calling constructor of eov plugin `%1%'")) %
            mPlugin);
    }

    PluginPtr plugin(call);
    return plugin;
}

}} // namespace vle eov
