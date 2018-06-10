
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;
typedef function<double(vector<double>)> f_double_vector;

int N;
int dim = 2;
double kT;
double dx;
double dp;
double omega;
double eps = pow(10, -12);


/************************ OLD FUNCTIONS ************************/


void write_points(string filename, int i, double E_avg, double E2_avg, double E_error, bool first) {
    FILE * file;
    if ( first ) {
        file = fopen(filename.c_str(), "w");
        fprintf(file, "%d,%.10lf,%.10lf,%.10lf", i, E_avg, E2_avg, E_error );
    }
    else {
        file = fopen(filename.c_str(), "a");
        fprintf(file, "\n%d,%.10lf,%.10lf,%.10lf", i, E_avg, E2_avg, E_error );
    }
}


double random_range(double start, double end) {
    return start + (end-start)*((float) rand()) / ((float) RAND_MAX);
}

double random_norm() {
    return ((float) rand()) / ((float) RAND_MAX);
}

double SHO( vector<double> Xn ) {
    double r2 = 0.0;
    for (int i=0; i<dim; i++)
        r2 += Xn[i]*Xn[i];
    return r2*omega*omega/2.0;
}

double KE( vector<double> Pn ) {
    double p2 = 0.0;
    for (int i=0; i<dim; i++)
        p2 += Pn[i]*Pn[i];
    return p2/2.0;
}

int update_x(vector<double> &Xn, int i, double delta, f_double_vector potential) {
    double x0, V0, V1, P;
    double step, random;
    x0 = Xn[i];
    V0 = potential(Xn);
    
    step = random_range(-delta, delta);
    Xn[i] += step;
    V1 = potential(Xn);
    
    if (V1 > V0) {
        P = exp(-V1/kT)/exp(-V0/kT);
        random = random_norm();
        if (random >= P) {
            Xn[i] = x0;
            return 0;
        }
    }
    return 1;
}

int update_p(vector<double> &Pn, int i, double delta, f_double_vector kinetic) {
    double p0, T0, T1, P;
    double step, random;
    p0 = Pn[i];
    T0 = kinetic(Pn);
    
    step = random_range(-delta, delta);
    Pn[i] += step;
    T1 = kinetic(Pn);
    
    if (T1 > T0) {
        P = exp(-T1/kT)/exp(-T0/kT);
        random = random_norm();
        if (random >= P) {
            Pn[i] = p0;
            return 0;
        }
    }
    return 1;
}

void update( vector<vector<double> > &X, vector<vector<double> > &P, f_double_vector kinetic, f_double_vector potential) {
    int x_accepted = 0, p_accepted = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<dim; j++) {
            x_accepted += update_x( X[i], j, dx, potential );
            p_accepted += update_p( P[i], j, dp, kinetic );
        }
    }
}

void update_totals(vector<vector<double> > &X, vector<vector<double> > &P, f_double_vector kinetic, f_double_vector potential, double &E_tot, double &E2_tot, double &E_avg, double &E2_avg, double &E_error, int count){
    double E = 0;
    for (int i=0; i < N; i++) {
        E = kinetic(P[i]) + potential(X[i]) ;
        E_tot += E;
        E2_tot += E*E;
    }
    E_avg = E_tot/(N*count);
    E2_avg = E2_tot/(N*count);
    E_error = sqrt( (E2_avg - E_avg*E_avg) ) /sqrt(N*count);
}



/************************ NEW FUNCTIONS ************************/

//Temporary function to set up horizontal/vertical barriers, replace with reading from a file
void initializeBarriers(vector< vector<double> > &HBarriers, vector< vector<double> > &VBarriers) {
    vector<double> barrier(3,0.0);
    barrier[2] = 1.0;
    HBarriers.push_back(barrier);
    VBarriers.push_back(barrier);
    barrier[0] = 1.0;
    HBarriers.push_back(barrier);
    VBarriers.push_back(barrier);
    barrier[0] = 0.5;
    barrier[2] = 0.45;
    VBarriers.push_back(barrier);
    barrier[1] = 0.55;
    barrier[2] = 1.0;
    VBarriers.push_back(barrier);
}

//Recursive function to update a particle's position by reflecting off any barriers
void bounce(vector<double> &Xn, vector<double> &Vn, vector< vector<double> > HBarriers, vector< vector<double> > VBarriers, double dt) {
    vector<double> newXn = Xn;
    vector<double> newVn = Vn;
    pair<double,int> interval(1.0, -1);
    
    for (int i=0; i<dim; i++)
        newXn[i] = Xn[i] + Vn[i]*dt;
    
    double fraction, xtemp, ytemp;
    for (vector<double> H: HBarriers) {
        if ( ( fabs(Xn[1]-H[0]) > eps ) && ( (Xn[1]-H[0])*(newXn[1]-H[0]) <= 0 ) ) {
            fraction = fabs(Xn[1]-H[0])/fabs(newXn[1]-Xn[1]);
            xtemp = Xn[0] + Vn[0]*dt*fraction;
            if ( (fraction < interval.first) && (H[1] <= xtemp ) && ( xtemp <= H[2]) )
                interval = pair<double,int> (fraction, 0);
        }
    }
    for (vector<double> V: VBarriers) {
        if ( ( fabs(Xn[0]-V[0]) > eps ) && ( (Xn[0]-V[0])*(newXn[0]-V[0]) <= 0 ) ) {
            fraction = fabs(Xn[0]-V[0])/fabs(newXn[0]-Xn[0]);
            ytemp = Xn[1] + Vn[1]*dt*fraction;
            if ( (fraction < interval.first) && ( V[1] <= ytemp ) && ( ytemp <= V[2] ) )
                interval = pair<double,int> (fraction, 1);
        }
    }
    
    if (interval.second >= 0) {
        for (int i=0; i<dim; i++)
            newXn[i] = Xn[i] + Vn[i]*dt*interval.first;
        if (interval.second == 0)
            newVn[1] *= -1;
        if (interval.second == 1)
            newVn[0] *= -1;
        bounce(newXn, newVn, HBarriers, VBarriers, dt*(1-interval.first) );
    }
    Xn = newXn;
    Vn = newVn;
}



int main(int argc, const char * argv[]) {
    srand(time(NULL));
    
    /*
     string output_directory = argv[1];
     kT = atof(argv[2]);
     omega = atof(argv[3]);
     N = atoi(argv[4]);
     int N_steps = atoi(argv[5]);
     int N_warmup = atoi(argv[6]);;
     int sample_freq = atoi(argv[7]);;
     dx = atof(argv[8]);
     dp = atof(argv[9]);
     
     int count = 0;
     double E_tot = 0, E2_tot = 0, E_avg = 0, E2_avg = 0, E_error = INFINITY;
     vector< vector<double> > X(N, vector<double>(dim, 0.0) );
     vector< vector<double> > P(N, vector<double>(dim, 0.0) );
     
     for (int i=0; i<N_steps; i++) {
     update(X, P, KE, SHO);
     if (i >= N_warmup && i%sample_freq == 0) {
     count++;
     update_totals(X, P, KE, SHO, E_tot, E2_tot, E_avg, E2_avg, E_error, count);
     write_points(output_directory, i, E_avg, E2_avg, E_error, (count==1) );
     }
     }
     */
    
    kT = 1.0;
    N = 1;
    int N_steps = 500;
    int N_warmup = 100;
    int sample_freq = 1;
    dx = 1.;
    dp = 1.;
    double dt = 0.1;
    
    vector< vector<double> > X(N, vector<double>(dim, 0.0) );
    vector< vector<double> > P(N, vector<double>(dim, 0.0) );
    vector< vector<double> > HBarriers, VBarriers;
    
    initializeBarriers(HBarriers, VBarriers);
    X[0][0] = 0.2;
    X[0][1] = 0.2;
    P[0][0] = -0.18683;
    P[0][1] = -0.1231;
    
    
    
    
    cout << X[0][0] << "\t" << X[0][1] << endl;
    for (int i=0; i<N_steps; i++) {
        bounce(X[0], P[0], HBarriers, VBarriers, dt);
        cout << X[0][0] << "\t" << X[0][1] << endl;
    }
    
    return 0;
}
