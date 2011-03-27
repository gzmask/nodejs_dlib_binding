// Copyright (C) 2010  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.


#include <dlib/matrix.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "../stl_checked.h"
#include "../array.h"
#include "../rand.h"
#include "checkerboard.h"
#include <dlib/statistics.h>

#include "tester.h"
#include <dlib/svm.h>


namespace  
{

    using namespace test;
    using namespace dlib;
    using namespace std;

    logger dlog("test.svm_c_linear");

    typedef matrix<double, 0, 1> sample_type;
    typedef std::vector<std::pair<unsigned int, double> > sparse_sample_type;

// ----------------------------------------------------------------------------------------

    void get_simple_points (
        std::vector<sample_type>& samples,
        std::vector<double>& labels
    )
    {
        samples.clear();
        labels.clear();
        sample_type samp(2);

        samp = 0,0;
        samples.push_back(samp);
        labels.push_back(-1);

        samp = 0,1;
        samples.push_back(samp);
        labels.push_back(-1);

        samp = 3,0;
        samples.push_back(samp);
        labels.push_back(+1);

        samp = 3,1;
        samples.push_back(samp);
        labels.push_back(+1);
    }

// ----------------------------------------------------------------------------------------

    void get_simple_points_sparse (
        std::vector<sparse_sample_type>& samples,
        std::vector<double>& labels
    )
    {
        samples.clear();
        labels.clear();
        sparse_sample_type samp;

        samp.push_back(make_pair(0, 0.0));
        samp.push_back(make_pair(1, 0.0));
        samples.push_back(samp);
        labels.push_back(-1);

        samp.clear();
        samp.push_back(make_pair(0, 0.0));
        samp.push_back(make_pair(1, 1.0));
        samples.push_back(samp);
        labels.push_back(-1);

        samp.clear();
        samp.push_back(make_pair(0, 3.0));
        samp.push_back(make_pair(1, 0.0));
        samples.push_back(samp);
        labels.push_back(+1);

        samp.clear();
        samp.push_back(make_pair(0, 3.0));
        samp.push_back(make_pair(1, 1.0));
        samples.push_back(samp);
        labels.push_back(+1);
    }

// ----------------------------------------------------------------------------------------

    void test_sparse (
    )
    {
        print_spinner();
        dlog << LINFO << "test with sparse vectors";
        std::vector<sparse_sample_type> samples;
        std::vector<double> labels;

        sample_type samp;

        get_simple_points_sparse(samples,labels);

        svm_c_linear_trainer<sparse_linear_kernel<sparse_sample_type> > trainer;
        trainer.set_c(1e4);
        //trainer.be_verbose();
        trainer.set_epsilon(1e-8);


        double obj;
        decision_function<sparse_linear_kernel<sparse_sample_type> > df = trainer.train(samples, labels, obj);
        dlog << LDEBUG << "obj: "<< obj;
        DLIB_TEST_MSG(abs(obj - 0.72222222222) < 1e-8, obj);

        DLIB_TEST(abs(df(samples[0]) - (-1)) < 1e-6);
        DLIB_TEST(abs(df(samples[1]) - (-1)) < 1e-6);
        DLIB_TEST(abs(df(samples[2]) - (1)) < 1e-6);
        DLIB_TEST(abs(df(samples[3]) - (1)) < 1e-6);
    }

// ----------------------------------------------------------------------------------------

    void test_dense (
    )
    {
        print_spinner();
        dlog << LINFO << "test with dense vectors";
        std::vector<sample_type> samples;
        std::vector<double> labels;

        sample_type samp;

        get_simple_points(samples,labels);

        svm_c_linear_trainer<linear_kernel<sample_type> > trainer;
        trainer.set_c(1e4);
        //trainer.be_verbose();
        trainer.set_epsilon(1e-8);


        double obj;
        decision_function<linear_kernel<sample_type> > df = trainer.train(samples, labels, obj);
        dlog << LDEBUG << "obj: "<< obj;
        DLIB_TEST_MSG(abs(obj - 0.72222222222) < 1e-8, obj);
        // There shouldn't be any margin violations since this dataset is so trivial.  So that means the objective
        // should be exactly the squared norm of the decision plane (times 0.5).
        DLIB_TEST_MSG(abs(length_squared(df.basis_vectors(0))*0.5 + df.b*df.b*0.5 - 0.72222222222) < 1e-8, 
                      length_squared(df.basis_vectors(0))*0.5 + df.b*df.b*0.5);

        DLIB_TEST(abs(df(samples[0]) - (-1)) < 1e-6);
        DLIB_TEST(abs(df(samples[1]) - (-1)) < 1e-6);
        DLIB_TEST(abs(df(samples[2]) - (1)) < 1e-6);
        DLIB_TEST(abs(df(samples[3]) - (1)) < 1e-6);
    }

// ----------------------------------------------------------------------------------------

    class svm_c_linear_tester : public tester
    {
    public:
        svm_c_linear_tester (
        ) :
            tester ("test_svm_c_linear",
                    "Runs tests on the svm_c_linear_trainer.")
        {}

        void perform_test (
        )
        {
            test_dense();
            test_sparse();
        }
    } a;

}



