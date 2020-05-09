/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

package si.tano.vremenar;

import android.app.UiModeManager;
import android.content.Context;
import android.content.res.Configuration;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.WindowInsets;

import ly.count.android.sdk.Countly;
import ly.count.android.sdk.CountlyConfig;

import org.qtproject.qt5.android.bindings.QtActivity;

class VremenarCountlyNativeInterface
{
    public static native String appKey();
    public static native String endpoint();
    public static native String salt();
}

public class VremenarActivity extends QtActivity
{
    public boolean isAndroidTV() {
        UiModeManager uiModeManager = (UiModeManager) getSystemService(UI_MODE_SERVICE);
        if (uiModeManager.getCurrentModeType() == Configuration.UI_MODE_TYPE_TELEVISION) {
            return true;
        }
        return false;
    }

    public int[] getSafeAreMargins() {
        int[] margins = new int[4];

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            View decorView = getWindow().getDecorView();
            WindowInsets insets = decorView.getRootWindowInsets();
            margins[0] = insets.getStableInsetTop();
            margins[1] = insets.getStableInsetBottom();
            margins[2] = insets.getStableInsetLeft();
            margins[3] = insets.getStableInsetRight();
        } else {
            margins[0] = 0;
            margins[1] = 0;
            margins[2] = 0;
            margins[3] = 0;
        }

        return margins;
    }

    public void recordEvent(String event) {
        Countly.sharedInstance().events().recordEvent(event);
    }

    @Override
    protected void onCreateHook(Bundle savedInstanceState) {
        this.QT_ANDROID_DEFAULT_THEME = "VremenarTheme";

        super.onCreateHook(savedInstanceState);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            View decorView = getWindow().getDecorView();
            // Hide the status bar.
            int uiOptions = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
            decorView.setSystemUiVisibility(uiOptions);
        }

        // Initialise Countly
        CountlyConfig config = new CountlyConfig(this, VremenarCountlyNativeInterface.appKey(), VremenarCountlyNativeInterface.endpoint());
        config.setLoggingEnabled(true);
        config.setViewTracking(false);
        config.enableCrashReporting();
        config.setParameterTamperingProtectionSalt(VremenarCountlyNativeInterface.salt());

        Countly.sharedInstance().init(config);
        Countly.sharedInstance().onCreate(this);
    }

    @Override
    public void onStart()
    {
        super.onStart();
        Countly.sharedInstance().onStart(this);
    }

    @Override
    public void onStop()
    {
        Countly.sharedInstance().onStop();
        super.onStop();
    }

    @Override
    public void onConfigurationChanged (Configuration newConfig){
        super.onConfigurationChanged(newConfig);
        Countly.sharedInstance().onConfigurationChanged(newConfig);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            View decorView = getWindow().getDecorView();
            // Hide the status bar.
            int uiOptions = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
            decorView.setSystemUiVisibility(uiOptions);
        }
    }
} 
