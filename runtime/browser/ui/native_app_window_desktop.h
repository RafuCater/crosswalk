// Copyright (c) 2015 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_RUNTIME_BROWSER_UI_NATIVE_APP_WINDOW_DESKTOP_H_
#define XWALK_RUNTIME_BROWSER_UI_NATIVE_APP_WINDOW_DESKTOP_H_

#include <string>

#include "content/public/browser/download_manager_delegate.h"
#include "ui/views/controls/button/label_button.h"
#include "ui/shell_dialogs/select_file_dialog.h"
#include "xwalk/runtime/browser/ui/native_app_window_views.h"

namespace views {
class WebView;
class Textfield;
class ProgressBar;
}

namespace content {
class DownloadItem;
}

namespace xwalk {
class DownloadBarView;

class NativeAppWindowDesktop : public NativeAppWindowViews,
                               public views::ButtonListener,
                               public ui::SelectFileDialog::Listener {
 public:
  explicit NativeAppWindowDesktop(const NativeAppWindow::CreateParams& params);
  ~NativeAppWindowDesktop() override;

  void SetLoadProgress(double progress);
  void SetAddressURL(const std::string& url);
  void UpdateWebViewPreferredSize();
  void AddDownloadItem(content::DownloadItem* download_item,
      const content::DownloadTargetCallback& callback,
      const base::FilePath& suggested_path);

 private:
  class AddressView;

  // NativeAppWindowViews implementation.
  void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

  // ButtonListener implementation.
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  // SelectFileDialog::Listener implementation.
  void FileSelected(const base::FilePath& path,
      int index,
      void* params) override;
  void FileSelectionCanceled(void* params) override;

  void InitStandaloneUI();
  void InitMinimalUI();

  // Toolbar view contains forward/backward/reload button and URL entry.
  views::View* toolbar_view_;
  views::LabelButton* back_button_;
  views::LabelButton* forward_button_;
  views::LabelButton* refresh_button_;
  views::LabelButton* stop_button_;
  AddressView* address_bar_;
  views::View* contents_view_;
  DownloadBarView* download_bar_view_;
  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;

  DISALLOW_COPY_AND_ASSIGN(NativeAppWindowDesktop);
};

inline NativeAppWindowDesktop* ToNativeAppWindowDesktop(
    NativeAppWindow* window) {
  return static_cast<NativeAppWindowDesktop*>(window);
}

}  // namespace xwalk

#endif  // XWALK_RUNTIME_BROWSER_UI_NATIVE_APP_WINDOW_DESKTOP_H_
