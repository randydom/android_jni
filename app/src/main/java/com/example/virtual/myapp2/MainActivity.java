package com.example.virtual.myapp2;

import android.os.Bundle;
import android.provider.Settings;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public native Object stringFromApayi() throws ApayiException;
    public native Object getPaymentWithRefundByPaymentId(String payment_id) throws ApayiException;
    public native Object getRefundsForPaymentId(String payment_id, int count);
    public native void captureByPaymentId(String txn_id, String amount, String currency);

    static {
        System.loadLibrary("apayi-user");
        //System.loadLibrary("apayi");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        final Button button1= (Button)findViewById(R.id.button);

        button1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                final TextView textview = (TextView) findViewById(R.id.textHello);
                try {
                    Payment p = (Payment)getPaymentWithRefundByPaymentId("pay_6d905050b6162a5b");
                    System.out.println("************************HHHHHH*****");
                    System.out.println(p.getCreated_at());
                    //System.out.println(p.getCreated_at());
                    System.out.println(p.getId());
                    //textview.setText(Integer.toString(p.getCreated_at()));

                    //System.out.println(p.getRefunds().get(0).getId());

                    textview.setText(p.getRefunds().get(0).getId());

                    captureByPaymentId("pay_d54f0718564aa4c4","1000","INR");

                } catch (ApayiException e) {

                    textview.setText("apayi_exception" + e.getMessage());
                } catch (Exception e) {
                    //System.out.println(e.getMessage())
                    textview.setText(e.getMessage());
                }
                //String textSetter = stringFromApayi();
                //textview.setText(textSetter);
            }
        });



        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
