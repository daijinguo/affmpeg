package dai.android.ffmpeg.V;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import dai.android.ffmpeg.R;


public class FConfigActivity extends AppCompatActivity {

    private TextView mText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fconfig);

        findViewById(R.id.btn_3_2_ff_showConfig).setOnClickListener(mListener);
        findViewById(R.id.btn_3_3_ff_Protocol).setOnClickListener(mListener);
        findViewById(R.id.btn_3_4_ff_Format).setOnClickListener(mListener);
        findViewById(R.id.btn_3_5_ff_Codec).setOnClickListener(mListener);
        findViewById(R.id.btn_3_6_ff_Filter).setOnClickListener(mListener);
        findViewById(R.id.btn_3_7_abi_info).setOnClickListener(mListener);

        mText = findViewById(R.id.textShow);
    }

    private native String getAvcodecCconfiguration();

    private native String avFilterInfo();

    private native String avCodecInfo();

    private native String avFormatInfo();

    private native String urlProtocolInfo();

    private native String getAbiInfo();

    private View.OnClickListener mListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            switch (v.getId()) {
                case R.id.btn_3_2_ff_showConfig: {
                    String strConfig = getAvcodecCconfiguration();
                    mText.setText(strConfig);
                    return;
                }

                case R.id.btn_3_3_ff_Protocol: {
                    String str = urlProtocolInfo();
                    mText.setText(str);
                    return;
                }

                case R.id.btn_3_4_ff_Format: {
                    String str = avFormatInfo();
                    mText.setText(str);
                    return;
                }

                case R.id.btn_3_5_ff_Codec: {
                    String str = avCodecInfo();
                    mText.setText(str);
                    return;
                }

                case R.id.btn_3_6_ff_Filter: {
                    String str = avFilterInfo();
                    mText.setText(str);
                    return;
                }

                case R.id.btn_3_7_abi_info: {
                    String str = getAbiInfo();
                    mText.setText(str);
                    return;
                }
            }


        }
    };
}
