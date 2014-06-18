#pragma once

#include <cassert>

namespace data
{

// define some helper types that can be used to pass simulation
// data around without haveing to pass individual parameters
struct Discretization
{
    int nx;       // x dimension
    int ny;       // y dimension
    int nt;       // number of time steps
    //TODO wherever you see this cause an error, double check if we want global or local value
    //int N;        // total number of grid points
    double dt;    // time step size
    double dx;    // distance between grid points
    double alpha; // dx^2/(D*dt)
};

struct SubDomain
{
    // initialize a subdomain
    void init(int, int, Discretization&);

    // print subdomain information
    void print();

    // i and j dimensions of the global decomposition
    int ndomx;
    int ndomy;

    // the i and j index of this sub-domain
    int domx;
    int domy;

    // the i and j bounding box of this sub-domain
    int startx;
    int starty;
    int endx;
    int endy;

    // the rank of neighbouring domains
    int neighbour_north;
    int neighbour_east;
    int neighbour_south;
    int neighbour_west;

    // mpi info
    int size;
    int rank;

    // boolean flags that indicate whether the sub-domain is on 
    // any of the 4 global boundaries
    bool on_boundary_north;
    int on_boundary_south;
    int on_boundary_east;
    int on_boundary_west;

    // x and y dimension in grid points of the sub-domain
    int nx;
    int ny;

    // total number of grid points
    int N;
};

// thin wrapper around a pointer that can be accessed as either a 2D or 1D array
// Field has dimension xdim * ydim in 2D, or length=xdim*ydim in 1D
class Field {
    public:
    // default constructor
    Field()
    :   ptr_(0),
        xdim_(0),
        ydim_(0),
        own_(false)
    {};

    // constructor
    explicit Field(double* ptr, int xdim, int ydim)
    :   ptr_(ptr),
        xdim_(xdim),
        ydim_(ydim),
        own_(false)
    {
        assert(xdim>0 && ydim>0);
    };

    // constructor
    Field(int xdim, int ydim)
    :   xdim_(xdim),
        ydim_(ydim),
        own_(true)
    {
        assert(xdim>0 && ydim>0);
        ptr_ = new double[xdim*ydim];
    };

    // destructor
    ~Field() {
        free();
    }

    void init(int xdim, int ydim) {
        assert(xdim>0 && ydim>0);
        free();
        ptr_ = new double[xdim*ydim];
        xdim_ = xdim;
        ydim_ = ydim;
        own_ = true;
    }

    double* data() {
        return ptr_;
    }

    const double* data() const {
        return ptr_;
    }

    // access via (i,j) pair
    inline double& operator() (int i, int j) {
        return ptr_[i+j*xdim_];
    }

    inline double const& operator() (int i, int j) const  {
        return ptr_[i+j*xdim_];
    }

    // access as a 1D field
    inline double & operator[] (int i) {
        return ptr_[i];
    }

    inline double const& operator[] (int i) const {
        return ptr_[i];
    }

    int xdim() const {
        return xdim_;
    }

    int ydim() const {
        return ydim_;
    }

    int length() const {
        return xdim_*ydim_;
    }

    private:

    void free() {
        if(own_ && ptr_)
            delete[] ptr_;
        xdim_=0;
        ydim_=0;
        own_=false;
    }

    double* ptr_;
    int xdim_;
    int ydim_;

    bool own_; // flag whether we own the memory or not
};

// fields that hold the solution
extern Field x_new; // 2d
extern Field x_old; // 2d

// fields that hold the boundary values
extern Field bndN; // 1d
extern Field bndE; // 1d
extern Field bndS; // 1d
extern Field bndW; // 1d

// buffers used in boundary exchange
extern Field buffN;
extern Field buffE;
extern Field buffS;
extern Field buffW;

extern Discretization options;
extern SubDomain      domain;

} // namespace data
