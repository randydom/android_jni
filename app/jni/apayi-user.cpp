//#include<vector>

#include "apayi.h"
#include "apayi_exception.h"
#include<jni.h>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <exception>
#include <fstream>


using namespace std;
using namespace apayi;
extern "C" {
jobject Java_com_example_virtual_myapp2_MainActivity_stringFromApayi(
        JNIEnv *env, jobject thiz) {
    try {
        SECRET_KEY = "RGl7DwXio30HxRhIwAuJ6OC9f1f1jqWHKLquUPxGja7sQbbpETGWOSX4vybyKtZ+cQQZjjC7yJn7iMNJNXtyRw==";
        CLIENT_ID = "64f61699-1bf6-40af-bc4e-353775f51b1d";
        using apayi::payment;
        std::vector <payment> payments = get_payments();
        payment payment1 = get_payment_with_refunds_by_payment_id(payments[0].id());
        /*std::vector <std::string> payment_ids;
        for (int i=0;i<payments.size();i++)
        {
            std::string pay = payments[i].id();
            payment_ids.push_back(pay);

            // jstring _str = (*env).NewStringUTF(str);

            //(*env).CallVoidMethod(object, (*env).GetMethodID(clazz, "add", "(java/lang/Object)V"), str);

        }
        jclass vectorClass = env->FindClass("java/util/ArrayList");
        jfieldID fieldId = env->GetFieldID(vectorClass, "String", "S");
        jobject objArray = env->GetObjectField (obj, fieldId);
*/
        std::string payment_id = payment1.id();

        //const char* str = (const char *) payment_id.c_str();

        //return str;
        jclass paymentClass = env->FindClass("com/example/virtual/myapp2/Payment");
        jobject obj = env->NewObject(paymentClass, env->GetMethodID(paymentClass, "<init>", "()V"));


        jfieldID fieldCreatedAt = env->GetFieldID(paymentClass, "created_at", "I");
        env->SetIntField(obj, fieldCreatedAt, payment1.created_at());


        jfieldID fieldId = env->GetFieldID(paymentClass, "id", "Ljava/lang/String;");
        jstring str = env->NewStringUTF((const char *) payment_id.c_str());
        env->SetObjectField(obj, fieldId, str);

        jclass refundClass = env->FindClass("com/example/virtual/myapp2/Refund");

        /*jobject refundobj = env->NewObject(refundClass, env->GetMethodID(refundClass, "<init>", "()V"));


        jfieldID fieldCreatedAt_ref = env->GetFieldID(refundClass, "created_at", "I");
        env->SetIntField(refundobj,fieldCreatedAt_ref,refundlist[0].created_at());

        jfieldID fieldRefId = env->GetFieldID(refundClass, "id", "Ljava/lang/String;");
        jstring strRefund = env->NewStringUTF((const char *) refundlist[0].id().c_str());
        env->SetObjectField( refundobj, fieldRefId , strRefund);

*/

        jmethodID refund_init = env->GetMethodID(refundClass, "<init>", "()V");

        std::vector <refund> refundlist = payment1.refunds();

        jclass clsArrayList = env->FindClass("java/util/ArrayList");
        jmethodID constructor = env->GetMethodID(clsArrayList, "<init>", "()V");
        jobject objArrayList = env->NewObject(clsArrayList, constructor, "");
        jmethodID arrayListAdd = env->GetMethodID(clsArrayList, "add", "(Ljava/lang/Object;)Z");

        for (int i = 0; i < refundlist.size(); ++i) {
            jobject cur_refund = env->NewObject(refundClass, refund_init);

            jfieldID fieldCreatedAt_ref = env->GetFieldID(refundClass, "created_at", "I");
            env->SetIntField(cur_refund, fieldCreatedAt_ref, refundlist[i].created_at());

            jfieldID fieldRefId = env->GetFieldID(refundClass, "id", "Ljava/lang/String;");
            jstring strRefund = env->NewStringUTF((const char *) refundlist[i].id().c_str());
            env->SetObjectField(cur_refund, fieldRefId, strRefund);
            env->CallBooleanMethod(objArrayList, arrayListAdd, cur_refund);
        }
        /*jobjectArray refundObjectArray = (jobjectArray) env->NewObjectArray(refundlist.size(),refundClass, 0);

        for(int i = 0; i < refundlist.size(); ++i)
        {
            jobject cur_refund =  env->NewObject(refundClass,refund_init );

            jfieldID fieldCreatedAt_ref = env->GetFieldID(refundClass, "created_at", "I");
            env->SetIntField(cur_refund,fieldCreatedAt_ref,refundlist[i].created_at());

            jfieldID fieldRefId = env->GetFieldID(refundClass, "id", "Ljava/lang/String;");
            jstring strRefund = env->NewStringUTF((const char *) refundlist[i].id().c_str());
            env->SetObjectField( cur_refund, fieldRefId , strRefund);

            env->SetObjectArrayElement(refundObjectArray, i, cur_refund);
        }

*/
        jfieldID fieldId_refundList = env->GetFieldID(paymentClass, "refunds",
                                                      "Ljava/util/ArrayList;");
        env->SetObjectField(obj, fieldId_refundList, objArrayList);


        return obj;


    }
    catch (apayi_business_exception &e) {

        jclass jcls = env->FindClass("com/example/virtual/myapp2/ApayiException");
        jboolean flag = env->ExceptionCheck();
        if (flag) {
            env->ExceptionClear();
            //* code to handle exception *//*
        }
        env->ThrowNew(jcls, e.what());
        //return;

        // jstring str = env->NewStringUTF((const char *) e.what()   );
        // return str ;
    }
    catch (apayi_exception &e) {
        jclass jcls = env->FindClass("java/lang/Exception");
        jboolean flag = env->ExceptionCheck();
        if (flag) {
            env->ExceptionClear();
            //* code to handle exception *//*
        }
        env->ThrowNew(jcls, e.what());
        // return;
    }
    catch (std::exception &e) {
        jclass jcls = env->FindClass("java/lang/Exception");
        //  jboolean flag = env->ExceptionCheck();
        // if (flag) {
        //      env->ExceptionClear();
        // }
        // env->ThrowNew(jcls, e.what());
        //jstring str = env->NewStringUTF((const char *) e.what()   );
        // return str ;
    }

}


jobject Java_com_example_virtual_myapp2_MainActivity_getPaymentWithRefundByPaymentId(
        JNIEnv *env, jobject thiz, jstring payment_id) {
    try {
        SECRET_KEY = "RGl7DwXio30HxRhIwAuJ6OC9f1f1jqWHKLquUPxGja7sQbbpETGWOSX4vybyKtZ+cQQZjjC7yJn7iMNJNXtyRw==";
        CLIENT_ID = "64f61699-1bf6-40af-bc4e-353775f51b1d";
        using apayi::payment;
        // payment payment1 = get_payment_with_refunds_by_payment_id("pay_6d905050b6162a5b");
        const char *str_payment_id = (env)->GetStringUTFChars(payment_id, NULL);
        payment payment1 = get_payment_with_refunds_by_payment_id(str_payment_id);
        env->ReleaseStringUTFChars(payment_id, str_payment_id);
        jclass paymentClass = env->FindClass("com/example/virtual/myapp2/Payment");
        jobject obj = env->NewObject(paymentClass, env->GetMethodID(paymentClass, "<init>", "()V"));


        jfieldID fieldCreatedAt = env->GetFieldID(paymentClass, "created_at", "I");
        env->SetIntField(obj, fieldCreatedAt, payment1.created_at());


        jfieldID fieldId = env->GetFieldID(paymentClass, "id", "Ljava/lang/String;");
        jstring str = env->NewStringUTF((const char *) payment1.id().c_str());
        env->SetObjectField(obj, fieldId, str);

        jclass refundClass = env->FindClass("com/example/virtual/myapp2/Refund");
        jmethodID refund_init = env->GetMethodID(refundClass, "<init>", "()V");

        std::vector <refund> refundlist = payment1.refunds();

        jclass clsArrayList = env->FindClass("java/util/ArrayList");
        jmethodID constructor = env->GetMethodID(clsArrayList, "<init>", "()V");
        jobject objArrayList = env->NewObject(clsArrayList, constructor, "");
        jmethodID arrayListAdd = env->GetMethodID(clsArrayList, "add", "(Ljava/lang/Object;)Z");
        jobject cur_refund;
        jstring strRefund;
        jfieldID fieldCreatedAt_ref = env->GetFieldID(refundClass, "created_at", "I");
        jfieldID fieldRefId = env->GetFieldID(refundClass, "id", "Ljava/lang/String;");


        for (int i = 0; i < refundlist.size(); ++i) {
            cur_refund = env->NewObject(refundClass, refund_init);

            env->SetIntField(cur_refund, fieldCreatedAt_ref, refundlist[i].created_at());

            strRefund = env->NewStringUTF((const char *) refundlist[i].id().c_str());
            env->SetObjectField(cur_refund, fieldRefId, strRefund);
            env->CallBooleanMethod(objArrayList, arrayListAdd, cur_refund);
        }
        //env->DeleteLocalRef(cur_refund);
        //env->DeleteLocalRef(strRefund);
        //env->DeleteLocalRef(fieldCreatedAt_ref);
        //env->DeleteLocalRef(fieldRefId);


        jfieldID fieldId_refundList = env->GetFieldID(paymentClass, "refunds",
                                                      "Ljava/util/ArrayList;");
        env->SetObjectField(obj, fieldId_refundList, objArrayList);

        return obj;


    }
    catch (apayi_business_exception &e) {
        jclass jcls = env->FindClass("com/example/virtual/myapp2/ApayiException");
        jboolean flag = env->ExceptionCheck();
        if (flag) {
            env->ExceptionClear();
        }
        env->ThrowNew(jcls, e.what());
    }
    catch (apayi_exception &e) {
        jclass jcls = env->FindClass("java/lang/Exception");
        jboolean flag = env->ExceptionCheck();
        if (flag) {
            env->ExceptionClear();
        }
        env->ThrowNew(jcls, e.what());
    }
    catch (std::exception &e) {
        jclass jcls = env->FindClass("java/lang/Exception");
        jboolean flag = env->ExceptionCheck();
        if (flag) {
            env->ExceptionClear();
        }
        env->ThrowNew(jcls, e.what());
    }

}


void Java_com_example_virtual_myapp2_MainActivity_captureByPaymentId(
        JNIEnv *env, jobject thiz, jstring txn_id, jstring amount, jstring currency) {
    try {
        SECRET_KEY = "RGl7DwXio30HxRhIwAuJ6OC9f1f1jqWHKLquUPxGja7sQbbpETGWOSX4vybyKtZ+cQQZjjC7yJn7iMNJNXtyRw==";
        CLIENT_ID = "64f61699-1bf6-40af-bc4e-353775f51b1d";
        using apayi::payment;

        const char *str_txn_id = (env)->GetStringUTFChars(txn_id, NULL);
        const char *str_amount = (env)->GetStringUTFChars(amount, NULL);
        const char *str_currency = (env)->GetStringUTFChars(currency, NULL);

        //payment payment1 = get_payment_with_refunds_by_payment_id(str_payment_id);
        capture_by_payment_id(str_txn_id, str_amount, str_currency);

        env->ReleaseStringUTFChars(txn_id, str_txn_id);
        env->ReleaseStringUTFChars(amount, str_amount);
        env->ReleaseStringUTFChars(currency, str_currency);
    }
catch (apayi_business_exception &e) {
    jclass jcls = env->FindClass("com/example/virtual/myapp2/ApayiException");
    jboolean flag = env->ExceptionCheck();
    if (flag) {
        env->ExceptionClear();
    }
    env->ThrowNew(jcls, e.what());
}
catch (apayi_exception &e) {
    jclass jcls = env->FindClass("java/lang/Exception");
    jboolean flag = env->ExceptionCheck();
    if (flag) {
        env->ExceptionClear();
    }
    env->ThrowNew(jcls, e.what());
}
catch (std::exception &e) {
    jclass jcls = env->FindClass("java/lang/Exception");
    jboolean flag = env->ExceptionCheck();
    if (flag) {
        env->ExceptionClear();
    }
    env->ThrowNew(jcls, e.what());
}
}
}


