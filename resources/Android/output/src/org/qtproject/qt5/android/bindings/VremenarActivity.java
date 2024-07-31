/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

package si.tano.vremenar;

import android.Manifest;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.UiModeManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Insets;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowInsets;
import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailabilityLight;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.messaging.FirebaseMessaging;
import java.util.List;
import ly.count.android.sdk.Countly;
import ly.count.android.sdk.CountlyConfig;
import org.qtproject.qt.android.bindings.QtActivity;

class VremenarCountlyNativeInterface
{
    public static native String appKey();
    public static native String endpoint();
    public static native String salt();
}

public class VremenarActivity extends QtActivity
{
    private static final String TAG = "VremenarActivity";
    private boolean notificationsRequested = false;

    public boolean isAndroidTV()
    {
        UiModeManager uiModeManager = (UiModeManager)getSystemService(UI_MODE_SERVICE);
        if (uiModeManager.getCurrentModeType() == Configuration.UI_MODE_TYPE_TELEVISION) {
            return true;
        }
        return false;
    }

    public boolean isFireTV()
    {
        final String AMAZON_FEATURE_FIRE_TV = "amazon.hardware.fire_tv";
        return getPackageManager().hasSystemFeature(AMAZON_FEATURE_FIRE_TV);
    }

    public boolean checkPlayServices()
    {
        int resultCode = GoogleApiAvailabilityLight.getInstance().isGooglePlayServicesAvailable(this);
        return resultCode == ConnectionResult.SUCCESS;
    }

    public int[] getSafeAreMargins()
    {
        int[] margins = new int[4];

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            View decorView = getWindow().getDecorView();
            Insets insets = decorView.getRootWindowInsets().getInsetsIgnoringVisibility(WindowInsets.Type.systemBars());
            margins[0] = insets.top;
            margins[1] = insets.bottom;
            margins[2] = insets.left;
            margins[3] = insets.right;
        } else {
            View decorView = getWindow().getDecorView();
            WindowInsets insets = decorView.getRootWindowInsets();
            margins[0] = insets.getStableInsetTop();
            margins[1] = insets.getStableInsetBottom();
            margins[2] = insets.getStableInsetLeft();
            margins[3] = insets.getStableInsetRight();
        }

        return margins;
    }

    public void recordEvent(String event)
    {
        Countly.sharedInstance().events().recordEvent(event);
    }

    private void askNotificationPermission()
    {
        // This is only necessary for API Level > 33 (TIRAMISU)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            Log.d(TAG, "Asking for notifications permission");

            if (ContextCompat.checkSelfPermission(this, Manifest.permission.POST_NOTIFICATIONS) == PackageManager.PERMISSION_GRANTED) {
                // FCM SDK (and your app) can post notifications.
            } else {
                // Directly ask for the permission
                requestPermissions(new String[] {Manifest.permission.POST_NOTIFICATIONS}, 123);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        switch (requestCode) {
        case 123:
            // If request is cancelled, the result arrays are empty.
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Permission is granted. Continue the action or workflow
                // in your app.
                Log.d(TAG, "Notifications permission granted.");
            } else {
                // Explain to the user that the feature is unavailable because
                // the feature requires a permission that the user has denied.
                // At the same time, respect the user's decision. Don't link to
                // system settings in an effort to convince the user to change
                // their decision.
                Log.d(TAG, "Notifications permission not granted.");
            }
            return;
        }
    }

    public boolean notificationsSupported()
    {
        return checkPlayServices();
    }

    public boolean requestNotifications()
    {
        if (!checkPlayServices() || notificationsRequested) {
            return true;
        }

        askNotificationPermission();

        FirebaseMessaging.getInstance().getToken();
        notificationsRequested = true;

        return false;
    }

    public boolean areNotificationsSupported()
    {
        return checkPlayServices();
    }

    public boolean areNotificationsEnabled()
    {
        if (!checkPlayServices()) {
            return false;
        }

        NotificationManager manager = getSystemService(NotificationManager.class);
        if (!manager.areNotificationsEnabled()) {
            return false;
        }
        List<NotificationChannel> channels = manager.getNotificationChannels();
        for (NotificationChannel channel : channels) {
            if (channel.getImportance() == NotificationManager.IMPORTANCE_NONE) {
                return false;
            }
        }
        return true;
    }

    public void notificationsSubscribe(String topic)
    {
        if (!checkPlayServices()) {
            return;
        }

        FirebaseMessaging.getInstance().subscribeToTopic(topic).addOnCompleteListener(new OnCompleteListener<Void>() {
            @Override
            public void onComplete(@NonNull Task<Void> task)
            {
                if (!task.isSuccessful()) {
                    Log.d(TAG, "Topic subscribe failed.");
                }
            }
        });
    }

    public void notificationsUnsubscribe(String topic)
    {
        if (!checkPlayServices()) {
            return;
        }

        FirebaseMessaging.getInstance().unsubscribeFromTopic(topic).addOnCompleteListener(new OnCompleteListener<Void>() {
            @Override
            public void onComplete(@NonNull Task<Void> task)
            {
                if (!task.isSuccessful()) {
                    Log.d(TAG, "Topic unsubscribe failed.");
                }
            }
        });
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        // this.QT_ANDROID_DEFAULT_THEME = "VremenarTheme";

        super.onCreate(savedInstanceState);

        View decorView = getWindow().getDecorView();
        // Hide the status bar.
        int uiOptions = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
        decorView.setSystemUiVisibility(uiOptions);

        // Initialise notifications
        NotificationManager notificationManager = getSystemService(NotificationManager.class);
        notificationManager.createNotificationChannel(
            new NotificationChannel("vremenar_forecast", "Forecast", NotificationManager.IMPORTANCE_LOW));
        notificationManager.createNotificationChannel(
            new NotificationChannel("vremenar_alerts", "Weather Alerts", NotificationManager.IMPORTANCE_HIGH));

        // Initialise Countly
        CountlyConfig config = new CountlyConfig(this, VremenarCountlyNativeInterface.appKey(), VremenarCountlyNativeInterface.endpoint());
        config.setLoggingEnabled(true);
        config.setViewTracking(false);
        config.enableCrashReporting();
        config.setParameterTamperingProtectionSalt(VremenarCountlyNativeInterface.salt());

        Countly.sharedInstance().init(config);
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
    public void onConfigurationChanged(Configuration newConfig)
    {
        super.onConfigurationChanged(newConfig);
        Countly.sharedInstance().onConfigurationChanged(newConfig);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);

        View decorView = getWindow().getDecorView();
        // Hide the status bar.
        int uiOptions = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
        decorView.setSystemUiVisibility(uiOptions);
    }
}
