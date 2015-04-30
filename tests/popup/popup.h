// Copyright 2015 Samsung Electronics Co, Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WRT_RUNTIME_POPUP_H_
#define WRT_RUNTIME_POPUP_H_

#include <Evas.h>
#include <Elementary.h>

#include <string>
#include <vector>
#include <functional>

namespace wrt {

class NativeWindow;

class Popup {
 public:
  enum class ButtonType {
    OkButton,
    OkCancelButton,
    LoginCancelButton,
    AllowDenyButton
  };

  enum class EntryType {
    Edit,
    PwEdit
  };
  //static Popup* CreatePopup(NativeWindow* window);
  static Popup* CreatePopup(Evas_Object* window);

  // button
  void SetButtonType(ButtonType type);
  bool IsPositiveButton(Evas_Object* button);
  bool GetButtonResult() const;  // yes/allow/ok: true, the others: false

  void SetFirstEntry(const std::string& str_id, EntryType type);
  void SetSecondEntry(const std::string& str_id, EntryType type);
  std::string GetFirstEntryResult() const;
  std::string GetSecondEntryResult() const;

  // check box
  void SetCheckBox(const std::string& str_id = std::string());
  bool GetCheckBoxResult() const;

  // etc.
  void SetTitle(const std::string& str_id);
  void SetBody(const std::string& str_id);
  void SetResultHandler(std::function
      <void(Popup* popup, void* user_data)> handler, void* user_data);

  // Popup's actions
  void Show();
  void Hide();
  void Result(bool is_positive);

  // getter
  Evas_Object* popup() { return popup_; }

 private:
  Popup(Evas_Object* popup, Evas_Object* grid, Evas_Object* box);
  ~Popup();

  Evas_Object* popup_;
  Evas_Object* grid_;
  Evas_Object* box_;
  Evas_Object* button1_;
  Evas_Object* button2_;
  Evas_Object* entry1_;
  Evas_Object* entry2_;
  Evas_Object* check_box_;

  std::function<void(Popup* popup, void* user_data)> handler_;
  void* user_data_;

  bool enable_button_;
  bool result_button_;
  bool enable_entry_;
  std::string result_entry1_;
  std::string result_entry2_;
  bool enable_check_box_;
  bool result_check_box_;
};

}  // namespace wrt

#endif  // WRT_RUNTIME_POPUP_H_
