package dai.android.ffmpeg;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import dai.android.ffmpeg.V.FConfigActivity;
import dai.android.ffmpeg.V.SimpleLiveActivity;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");

        System.loadLibrary("ffmpeg");
        //System.loadLibrary("avcodec");
        //System.loadLibrary("avdevice");
        //System.loadLibrary("avfilter");
        //System.loadLibrary("avformat");
        //System.loadLibrary("avutil");
        //System.loadLibrary("swresample");
        //System.loadLibrary("swscale");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_1_ff_config).setOnClickListener(mListener);
        findViewById(R.id.btn_2_ff_simpleLive).setOnClickListener(mListener);
    }

    private View.OnClickListener mListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            switch (v.getId()) {
                case R.id.btn_1_ff_config: {
                    Intent intent = new Intent(MainActivity.this, FConfigActivity.class);
                    startActivity(intent);
                    return;
                }

                case R.id.btn_2_ff_simpleLive: {
                    Intent intent = new Intent(MainActivity.this, SimpleLiveActivity.class);
                    startActivity(intent);
                    return;
                }
            }

        }
    };


}
