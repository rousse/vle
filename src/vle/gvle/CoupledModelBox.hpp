/*
 * @file vle/gvle/CoupledModelBox.hpp
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


#ifndef GUI_COUPLEDMODELBOX_HPP
#define GUI_COUPLEDMODELBOX_HPP

#include <gtkmm.h>
#include <libglademm.h>
#include <vle/graph/CoupledModel.hpp>

namespace vle { namespace gvle {

class Modeling;
class GVLE;

class CoupledModelBox : public Gtk::TreeView
{
public:
    CoupledModelBox(Glib::RefPtr<Gnome::Glade::Xml> xml, Modeling* m, GVLE* gvle);

    void show(graph::CoupledModel* model);

protected:
class ModelColumns : public Gtk::TreeModelColumnRecord
    {
    public:

        ModelColumns() {
            add(m_col_name);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

private:

    class InputPortTreeView : public Gtk::TreeView
    {
    public:
	InputPortTreeView(BaseObjectType* cobject,
			  const Glib::RefPtr<Gnome::Glade::Xml>& /*refGlade*/);
	virtual ~InputPortTreeView();

	void applyRenaming(graph::CoupledModel* model);
	void build();
	void clearRenaming()
	    { mRenameList.clear(); }
	void setModel(graph::CoupledModel* model)
	    { mModel = model; }

    protected:
	virtual bool on_button_press_event(GdkEventButton *ev);
	virtual void onAdd();
	virtual void onRemove();
	virtual void onRename();

	// Signal handler for text area
	virtual void onEditionStarted(
	    Gtk::CellEditable* cellEditatble,
	    const Glib::ustring& path);
	virtual void onEdition(
	    const Glib::ustring& pathString,
	    const Glib::ustring& newName);

    private:
	typedef std::vector < std::pair < std::string,
					  std::string > > renameList;
	graph::CoupledModel* mModel;
	Gtk::Menu mMenuPopup;
	ModelColumns mColumnsInputPort;
	Glib::RefPtr<Gtk::ListStore> mRefTreeModelInputPort;

	int mColumnIn;
	bool mValidateRetry;
	std::string mOldName;
	Gtk::CellRendererText* mCellRenderer;
	Glib::ustring mInvalidTextForRetry;
	renameList mRenameList;
    };

    class OutputPortTreeView : public Gtk::TreeView
    {
    public:
	OutputPortTreeView(BaseObjectType* cobject,
			   const Glib::RefPtr<Gnome::Glade::Xml>& /*refGlade*/);
	virtual ~OutputPortTreeView();

	void applyRenaming(graph::CoupledModel* model);
	void build();
	void clearRenaming()
	    { mRenameList.clear(); }
	void setModel(graph::CoupledModel* model)
	    { mModel = model; }
    protected:
	virtual bool on_button_press_event(GdkEventButton *ev);

	virtual void onAdd();
	virtual void onRemove();
	virtual void onRename();

	// Signal handler for text area
	virtual void onEditionStarted(
	    Gtk::CellEditable* cellEditatble,
	    const Glib::ustring& path);
	virtual void onEdition(
	    const Glib::ustring& pathString,
	    const Glib::ustring& newName);

    private:
	typedef std::vector < std::pair < std::string,
					  std::string > > renameList;
	graph::CoupledModel* mModel;
	Gtk::Menu mMenuPopup;
	ModelColumns mColumnsOutputPort;
	Glib::RefPtr<Gtk::ListStore> mRefTreeModelOutputPort;

	int mColumnOut;
	bool mValidateRetry;
	std::string mOldName;
	Gtk::CellRendererText* mCellRenderer;
	Glib::ustring mInvalidTextForRetry;
	renameList mRenameList;
    };

    void applyPorts();
    void on_validate();
    void on_cancel();

    Glib::RefPtr<Gnome::Glade::Xml>        mXml;
    Modeling*                              mModeling;
    GVLE*                                  mGVLE;
    graph::CoupledModel*                   mGraphModel;
    graph::CoupledModel*                   mCurrentGraphModel;

    Gtk::Dialog*                           mDialog;
    Gtk::Label*                            mModelName;
    Gtk::Label*                            mModelNbChildren;


    InputPortTreeView*                     mInputPorts;
    OutputPortTreeView*                    mOutputPorts;


    Gtk::TreeView*                         mTreeViewOutput;
    ModelColumns                           mColumnsOutput;
    Glib::RefPtr<Gtk::ListStore>           mRefListOutput;

    Gtk::Button*                           mOkButton;
    Gtk::Button*                           mCancelButton;

};

} } // namespace vle gvle

#endif
