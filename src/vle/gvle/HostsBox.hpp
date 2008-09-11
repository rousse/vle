/**
 * @file vle/gvle/HostsBox.hpp
 * @author The VLE Development Team
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment (http://vle.univ-littoral.fr)
 * Copyright (C) 2003 - 2008 The VLE Development Team
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


#ifndef GUI_HOSTSBOX_HPP
#define GUI_HOSTSBOX_HPP

#include <vle/utils/Path.hpp>
#include <vle/utils/Host.hpp>
#include <sigc++/trackable.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/treeview.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <libglademm/xml.h>

namespace vle
{
namespace gvle {

/**
 * @brief A dialog box to get or set the hosts informations to user. A
 * thread is launch using socket information to test the existence of host
 * and the VLE simulator daemon.
 *
 */
class HostInformation : public sigc::trackable
{
public:
    HostInformation(Glib::RefPtr < Gnome::Glade::Xml > ref);

    ~HostInformation();

    /**
     * Run a dialog box, create the thread and read information if exist.
     *
     * @param host where get the host information.
     *
     * @return true if user select OK button, false otherwise.
     */
    bool run(utils::Host& host);

    /**
     * Clear the dialog box from all information.
     *
     */
    void clear();

    /**
     * Initialise the dialog box from host information passed in
     * parameters.
     *
     * @param host where get the host information.
     */
    void init(const utils::Host& host);

private:
    void thread();

    bool timer(int t);

    void close();

    Gtk::Entry*         mEntry;
    Gtk::SpinButton*    mSpinButtonPort;
    Gtk::SpinButton*    mSpinButtonProcess;
    Gtk::Label*         mLabelConnection;
    Gtk::Label*         mLabelDaemon;
    Gtk::Image*         mImageConnection;
    Gtk::Image*         mImageDaemon;
    Gtk::Dialog*        mDialog;
    Glib::Thread*       mThread;
    bool                mThreadRun;
    bool                mWaiting;
    bool                mPing;
    bool                mDaemon;
    std::string         mIP;
    int                 mPort;
    sigc::connection    mTimer;
    Glib::RefPtr < Gnome::Glade::Xml >  mRefXML;
};

/**
 * @brief Hosts dialog to select hosts, ports and processor for VLE
 * simulators. The format of the XML file is:
 * @code
 * <?xml version="1.0"?>
 *   <hosts>
 *     <host hostname="vle.univ-littoral.fr" port="8000" process="2" />
 *     <host hostname="193.49.192.226" port="934" process="2" />
 *      ...
 *   </hosts>
 * </xml>
 * @endcode
 */
class HostsBox : public sigc::trackable
{
public:
    /**
     * Build dialog box using the gvle.glade file.
     *
     * @throw Exception::Parse when error during parsing hosts file.
     */
    HostsBox(Glib::RefPtr < Gnome::Glade::Xml > ref);

    /**
     * Delete dialog box and kill Thread
     *
     */
    ~HostsBox();

    /**
     * Show dialog box.
     *
     */
    void run();

    /**
     * Test VLE daemon existence for hostname using port.
     *
     * @param hostname name of host using IP address or name. Example:
     * 193.49.192.226 or vle.univ-littoral.fr.
     * @param port port number
     * @return -1 if access error, 0 if VLE daemon not found, >= 1 for
     * number of processor found.
     */
    static int test_vle_existence(const Glib::ustring& hostname,
                                  int port);

    /**
     * Create user hosts file and fill it with only localhost information.
     * If a file already exist, do nothing.
     *
     * @return true user hosts file is created, false otherwise.
     */
    static bool build_only_localhost_user_hosts_file();

    /**
     * Return the user hosts filename.
     *
     * @return user hosts filename.
     */
    static inline Glib::ustring get_hosts_filename();


private:
    /**
     * Open user hosts file if exist and read it. If it does not exist, it
     * will be create with only a reference to localhost.
     */
    void init_hosts();

    void addHost();

    void modifyHost(const Gtk::TreeModel::Path& path,
                    Gtk::TreeViewColumn* column);

    void delHost();

    void redraw();

class Column : public Gtk::TreeModel::ColumnRecord
    {
    public:
        Column() {
            add(mHostname);
            add(mPort);
            add(mProcess);
            add(mImage);
        }

        Gtk::TreeModelColumn < std::string > mHostname;
        Gtk::TreeModelColumn < int > mPort;
        Gtk::TreeModelColumn < int > mProcess;
        Gtk::TreeModelColumn < Glib::RefPtr < Gdk::Pixbuf > > mImage;
    };

    Gtk::Dialog*        mDialog;
    Gtk::Button*        mAdd;
    Gtk::Button*        mDel;
    Gtk::Button*        mOk;
    Gtk::Button*        mCancel;
    Gtk::TreeView*      mTreeView;
    Gtk::Label*         mLabel;
    HostInformation     mHostInformation;
    utils::Hosts   mHosts;
    Column              mColumn;
    Glib::RefPtr < Gnome::Glade::Xml > mRefXML;
    Glib::RefPtr < Gtk::ListStore >     mListStore;
};

}
} // namespace vle gvle

#endif