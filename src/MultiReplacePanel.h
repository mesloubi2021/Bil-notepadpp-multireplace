// This file is part of Notepad++ project
// Copyright (C)2023 Thomas Knoefel

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef MULTI_REPLACE_PANEL_H
#define MULTI_REPLACE_PANEL_H

#include "DockingFeature\DockingDlgInterface.h"
#include "resource.h"
#include <string>
#include <vector>
#include <commctrl.h>


struct ReplaceItemData
{
    std::wstring findText;
    std::wstring replaceText;
    bool wholeWord = false;
    bool regexSearch = false;
    bool matchCase = false;
    bool extended = false;
};

typedef std::basic_string<TCHAR> generic_string;

class MultiReplacePanel : public DockingDlgInterface
{
public:
    MultiReplacePanel() :
        DockingDlgInterface(IDD_REPLACE_DIALOG),
        _replaceListView(NULL),
        _hDeleteIcon(NULL),
        _hEnabledIcon(NULL),
        deleteIconIndex(-1),
        enabledIconIndex(-1),
        _himl(NULL)
    {};

    virtual void display(bool toShow = true) const {
        DockingDlgInterface::display(toShow);
    };

    void setParent(HWND parent2set) {
        _hParent = parent2set;
    };

protected:
    virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
    static void addStringToComboBoxHistory(HWND hComboBox, const TCHAR* str, int maxItems = 10);
private:
    HWND _replaceListView;
    HICON _hDeleteIcon;
    HICON _hEnabledIcon;
    int deleteIconIndex;
    int enabledIconIndex;

    HIMAGELIST _himl;
    std::vector<ReplaceItemData> replaceListData;

    int convertExtendedToString(const TCHAR* query, TCHAR* result, int length);
    void clearAllMarks();
    void copyMarkedTextToClipboard();
    void markMatchingStrings(const TCHAR* findText, bool wholeWord, bool matchCase, bool regexSearch, bool extended);
    void findAndReplace(const TCHAR* findText, const TCHAR* replaceText, bool wholeWord, bool matchCase, bool regexSearch, bool extended);
    void insertReplaceListItem(const ReplaceItemData& itemData);
    void onCopyToListButtonClick();
    void onReplaceAllInListButtonClick();
    void createListViewColumns(HWND listView);
};

#endif // MULTI_REPLACE_PANEL_H