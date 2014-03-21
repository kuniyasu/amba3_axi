/*
 * amba3_axi_if.h
 *
 *  Created on: 2014/03/13
 *      Author: Kuniyasu
 */

#ifndef AMBA3_AXI_IF_H_
#define AMBA3_AXI_IF_H_

#include<systemc.h>
#include<tlm.h>
using namespace tlm;

#include "syn_fifo.h"

class BUFFERABLE{};
class NONBUFFERABLE{};
class REGSLICE{};

class PIN{};
class TLM2LT{};
class TLM2AT{};

#define TR_NAME(_name) (std::string(name())+"_"+std::string(_name)).c_str()
#define PIN_NAME(bname,_name_) (std::string(bname)+"_"+std::string(_name_)).c_str()


#define STALL(i) wait();while( i ){ wait(); }
//#define STALL(i) do{wait();}while( i )


template<class CFG> class amba3_axi_aw_sig;
template<class CFG> class amba3_axi_ar_sig;
template<class CFG> class amba3_axi_wd_sig;
template<class CFG> class amba3_axi_rd_sig;
template<class CFG> class amba3_axi_br_sig;
template<class CFG> class amba3_axi_w_sig;
template<class CFG> class amba3_axi_r_sig;
template<class CFG> class amba3_axi_sig;

template<class CFG> class amba3_axi_aw_base_initiator;
template<class CFG> class amba3_axi_ar_base_initiator;
template<class CFG> class amba3_axi_wd_base_initiator;
template<class CFG> class amba3_axi_rd_base_initiator;
template<class CFG> class amba3_axi_br_base_initiator;
template<class CFG> class amba3_axi_w_base_initiator;
template<class CFG> class amba3_axi_r_base_initiator;
template<class CFG> class amba3_axi_base_initiator;

template<class CFG, class BF> class amba3_axi_aw_initiator_;
template<class CFG, class BF> class amba3_axi_ar_initiator_;
template<class CFG, class BF> class amba3_axi_wd_initiator_;
template<class CFG, class BF> class amba3_axi_rd_initiator_;
template<class CFG, class BF> class amba3_axi_br_initiator_;

template<class CFG, class AW_BF,class WD_BF, class BR_BF> class amba3_axi_w_initiator_;
template<class CFG, class AR_BF,class RD_BF> class amba3_axi_r_initiator_;

template<class CFG, class AW_BF, class WD_BF, class BR_BF, class AR_BF, class RD_BF> class amba3_axi_initiator_;

class amba3_axi_type;
template<class CFG> class amba3_axi_address_type;
template<class CFG> class amba3_axi_wd_type;
template<class CFG> class amba3_axi_rd_type;
template<class CFG> class amba3_axi_resp_type;

// template?
class amba3_axi_type{
public:
	static const unsigned char ID_WIDTH = 4U;
	typedef sc_uint<ID_WIDTH> id_type;

	static const unsigned int ADDR_WIDTH = 32U;
	typedef sc_uint<ADDR_WIDTH> addr_type;

	static const unsigned int LEN_WIDTH = 32U;
	typedef sc_uint<LEN_WIDTH> len_type;

	static const unsigned int SIZE_WIDTH = 32U;
	typedef sc_uint<SIZE_WIDTH> size_type;

	static const unsigned int DATA_WIDTH = 64U;
	typedef sc_uint<DATA_WIDTH> data_type;
	//typedef sc_biguint<DATA_WIDTH> data_type;

	static const unsigned int STRB_WIDTH = DATA_WIDTH/8;
	typedef sc_uint<STRB_WIDTH> strb_type;

	static const unsigned int RESP_WIDTH = 4;
	typedef sc_uint<RESP_WIDTH> resp_type;


	static const unsigned int AW_FIFO_SIZE = 2U;
	static const unsigned int AW_FIFO_CNT_WIDTH = 1U;

	static const unsigned int AR_FIFO_SIZE = 2U;
	static const unsigned int AR_FIFO_CNT_WIDTH = 1U;

	static const unsigned int W_FIFO_SIZE = 2U;
	static const unsigned int W_FIFO_CNT_WIDTH = 1U;

	static const unsigned int R_FIFO_SIZE = 2U;
	static const unsigned int R_FIFO_CNT_WIDTH = 1U;

	static const unsigned int B_FIFO_SIZE = 2U;
	static const unsigned int B_FIFO_CNT_WIDTH = 1U;

};

template<class CFG=amba3_axi_type> class amba3_axi_address_type{
public:
	typedef amba3_axi_address_type<CFG> this_type;

	typename CFG::id_type id;
	typename CFG::addr_type addr;
	typename CFG::len_type len;
	typename CFG::size_type size;

	amba3_axi_address_type(){
		reset();
	}

	amba3_axi_address_type(const amba3_axi_address_type<CFG>& dt){
		this->id = dt.id;
		this->addr = dt.addr;
		this->len = dt.len;
		this->size = dt.size;
	}

	void reset(){}

	//TODO: implementation systemc data stuct method.

    inline bool operator == (const this_type& i) const {
    	return (this->id == i.id)&&(this->addr == i.addr)&&(this->len == i.len)&&(this->size == i.size);
    }

    inline this_type& operator = (const this_type& i) {
    	this->id = i.id;
    	this->addr = i.addr;
    	this->len = i.len;
    	this->size = i.size;

      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
//      sc_trace(tf,v.info, NAME + ".info");
//      sc_trace(tf,v.flag, NAME + ".flag");
    }

    inline friend ostream& operator << ( ostream& os,  this_type const & v ) {
      //os << "(" << v.info << "," << std::boolalpha << v.flag << ")";
      return os;
    }
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_type{
public:
	typedef amba3_axi_wd_type<CFG> this_type;

	typename CFG::id_type id;
	bool last;
	typename CFG::strb_type strb;
	typename CFG::data_type data;

	amba3_axi_wd_type(){
		reset();
	}

	amba3_axi_wd_type(const amba3_axi_wd_type<CFG>& dt){
		this->id = dt.id;
		this->last = dt.last;
		this->strb = dt.strb;
		this->data = dt.data;
	}

	void reset(){}

	//TODO: implementation systemc data stuct method.
    inline bool operator == (const this_type& i) const {
    	return (this->id == i.id)&&(this->last == i.last)&&(this->strb == i.strb)&&(this->data == i.data);
    }

    inline this_type& operator = (const this_type& i) {
    	this->id = i.id;
    	this->last = i.last;
    	this->strb = i.strb;
    	this->data = i.data;

      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
//      sc_trace(tf,v.info, NAME + ".info");
//      sc_trace(tf,v.flag, NAME + ".flag");
    }

    inline friend ostream& operator << ( ostream& os,  this_type const & v ) {
      //os << "(" << v.info << "," << std::boolalpha << v.flag << ")";
      return os;
    }
};

template<class CFG=amba3_axi_type> class amba3_axi_rd_type{
public:
	typedef amba3_axi_rd_type<CFG> this_type;

	typename CFG::id_type id;
	bool last;
	typename CFG::resp_type resp;
	typename CFG::data_type data;

	amba3_axi_rd_type(){
		reset();
	}

	amba3_axi_rd_type(const amba3_axi_rd_type<CFG>& dt){
		this->id = dt.id;
		this->last = dt.last;
		this->resp = dt.resp;
		this->data = dt.data;
	}

	void reset(){}

	//TODO: implementation systemc data stuct method.
    inline bool operator == (const this_type& i) const {
    	return (this->id == i.id)&&(this->last == i.last)&&(this->resp == i.resp)&&(this->data == i.data);
    }

    inline this_type& operator = (const this_type& i) {
    	this->id = i.id;
    	this->last = i.last;
    	this->resp = i.resp;
    	this->data = i.data;

      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
//      sc_trace(tf,v.info, NAME + ".info");
//      sc_trace(tf,v.flag, NAME + ".flag");
    }

    inline friend ostream& operator << ( ostream& os,  this_type const & v ) {
      //os << "(" << v.info << "," << std::boolalpha << v.flag << ")";
      return os;
    }
};

template<class CFG=amba3_axi_type> class amba3_axi_resp_type{
public:
	typedef amba3_axi_resp_type<CFG> this_type;

	typename CFG::id_type id;
	typename CFG::resp_type resp;

	amba3_axi_resp_type(){
		reset();
	}

	amba3_axi_resp_type(const amba3_axi_resp_type<CFG>& dt){
		this->id = dt.id;
		this->resp = dt.resp;
	}

	void reset(){}

	//TODO: implementation systemc data stuct method.
    inline bool operator == (const this_type& i) const {
    	return (this->id == i.id)&&(this->resp == i.resp);
    }

    inline this_type& operator = (const this_type& i) {
    	this->id = i.id;
    	this->resp = i.resp;
    	return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
//      sc_trace(tf,v.info, NAME + ".info");
//      sc_trace(tf,v.flag, NAME + ".flag");
    }

    inline friend ostream& operator << ( ostream& os,  this_type const & v ) {
      //os << "(" << v.info << "," << std::boolalpha << v.flag << ")";
      return os;
    }
};


template<class CFG=amba3_axi_type> class amba3_axi_aw_initiator_if_:public sc_interface {
public:
	typedef amba3_axi_address_type<CFG> data_type;
	virtual void aw_reset() = 0;
	virtual void b_put_aw(const data_type& aw) = 0;
	virtual bool nb_put_aw(const data_type& aw) = 0;
};

template<class CFG=amba3_axi_type> class amba3_axi_ar_initiator_if_:public sc_interface {
public:
	typedef amba3_axi_address_type<CFG> data_type;
	virtual void ar_reset() = 0;
	virtual void b_put_ar(const data_type& ar) = 0;
	virtual bool nb_put_ar(const data_type& ar) = 0;
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_initiator_if_:public sc_interface {
public:

};

template<class CFG=amba3_axi_type> class amba3_axi_rd_initiator_if_:public sc_interface {
public:

};

template<class CFG=amba3_axi_type> class amba3_axi_br_initiator_if_:public sc_interface {
public:

};



template<class CFG=amba3_axi_type> class amba3_axi_aw_target_if_:public sc_interface {
public:
	typedef amba3_axi_address_type<CFG> data_type;
	virtual void aw_reset() = 0;
	virtual void b_get_aw( data_type& aw) = 0;
	virtual bool nb_get_aw( data_type& aw) = 0;
};

template<class CFG=amba3_axi_type> class amba3_axi_ar_target_if_:public sc_interface {
public:
	typedef amba3_axi_address_type<CFG> data_type;
	virtual void ar_reset() = 0;
	virtual void b_get_ar( data_type& aw) = 0;
	virtual bool nb_get_ar( data_type& aw) = 0;
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_target_if_:public sc_interface {
public:

};

template<class CFG=amba3_axi_type> class amba3_axi_rd_target_if_:public sc_interface {
public:

};

template<class CFG=amba3_axi_type> class amba3_axi_br_target_if_:public sc_interface {
public:

};

template<class CFG=amba3_axi_type> class amba3_axi_aw_sig{
public:
	sc_signal<bool> awvalid;
	sc_signal<typename CFG::id_type> awid;
	sc_signal<typename CFG::addr_type> awaddr;
	sc_signal<typename CFG::len_type> awlen;
	sc_signal<typename CFG::size_type> awsize;
	sc_signal<bool> awready;

	amba3_axi_aw_sig(const char* name=sc_gen_unique_name("amba3_axi_aw_sig")){}
};

template<class CFG=amba3_axi_type> class amba3_axi_ar_sig{
public:
	sc_signal<bool> arvalid;
	sc_signal<typename CFG::id_type> arid;
	sc_signal<typename CFG::addr_type> araddr;
	sc_signal<typename CFG::len_type> arlen;
	sc_signal<typename CFG::size_type> arsize;
	sc_signal<bool> arready;

	amba3_axi_ar_sig(const char* name=sc_gen_unique_name("amba3_axi_ar_sig")){}
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_sig{
public:
	sc_signal<bool> wvalid;
	sc_signal<typename CFG::id_type> wid;
	sc_signal<bool> wlast;
	sc_signal<typename CFG::strb_type> wstrb;
	sc_signal<typename CFG::data_type> wdata;
	sc_signal<bool> wready;

	amba3_axi_wd_sig(const char* name=sc_gen_unique_name("amba3_axi_wd_sig")){}
};

template<class CFG=amba3_axi_type> class amba3_axi_rd_sig{
public:
	sc_signal<bool> rvalid;
	sc_signal<typename CFG::id_type> rid;
	sc_signal<bool> rlast;
	sc_signal<typename CFG::resp_type> rresp;
	sc_signal<typename CFG::data_type> rdata;
	sc_signal<bool> rready;

	amba3_axi_rd_sig(const char* name=sc_gen_unique_name("amba3_axi_rd_sig")){}
};

template<class CFG=amba3_axi_type> class amba3_axi_br_sig{
public:
	sc_signal<bool> bvalid;
	sc_signal<typename CFG::id_type> bid;
	sc_signal<typename CFG::resp_type> bresp;
	sc_signal<bool> bready;

	amba3_axi_br_sig(const char* name=sc_gen_unique_name("amba3_axi_br_sig")){}
};

template<class CFG=amba3_axi_type> class amba3_axi_w_sig:public amba3_axi_aw_sig<CFG>, public amba3_axi_wd_sig<CFG>, public amba3_axi_br_sig<CFG>{
public:
//	sc_signal<bool> awvalid;
//	sc_signal<CFG::id_type> awid;
//	sc_signal<CFG::addr_type> awaddr;
//	sc_signal<CFG::len_type> awlen;
//	sc_signal<CFG::size_type> awsize;
//	sc_signal<bool> awready;

//	sc_signal<bool> wvalid;
//	sc_signal<CFG::id_type> wid;
//	sc_signal<bool> wlast;
//	sc_signal<CFG::strb_type> wstrb;
//	sc_signal<CFG::data_type> wdata;
//	sc_signal<bool> wready;

//	sc_signal<bool> bvalid;
//	sc_signal<CFG::id_type> bid;
//	sc_signal<CFG::resp_type> bresp;
//	sc_signal<bool> bready;
};

template<class CFG=amba3_axi_type> class amba3_axi_r_sig:public amba3_axi_ar_sig<CFG>, public amba3_axi_rd_sig<CFG>{
public:
//	sc_signal<bool> arvalid;
//	sc_signal<CFG::id_type> arid;
//	sc_signal<CFG::addr_type> araddr;
//	sc_signal<CFG::len_type> arlen;
//	sc_signal<CFG::size_type> arsize;
//	sc_signal<bool> arready;

//	sc_signal<bool> rvalid;
//	sc_signal<CFG::id_type> rid;
//	sc_signal<bool> rlast;
//	sc_signal<CFG::resp_type> rresp;
//	sc_signal<CFG::data_type> rdata;
//	sc_signal<bool> rready;
};

template<class CFG=amba3_axi_type> class amba3_axi_sig
:public amba3_axi_aw_sig<CFG>
, public amba3_axi_wd_sig<CFG>
, public amba3_axi_br_sig<CFG>
,public amba3_axi_ar_sig<CFG>
, public amba3_axi_rd_sig<CFG>
{
public:

	amba3_axi_sig(const char* name=sc_gen_unique_name("amba3_axi_sig")){}
};




template<class CFG=amba3_axi_type> class amba3_axi_aw_base_initiator{
public:
	sc_out<bool> awvalid;
	sc_out<typename CFG::id_type> awid;
	sc_out<typename CFG::addr_type> awaddr;
	sc_out<typename CFG::len_type> awlen;
	sc_out<typename CFG::size_type> awsize;
	sc_in<bool> awready;

	amba3_axi_aw_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_aw_base_initiator"))
	:awvalid(PIN_NAME(name,"awvalid"))
	,awid(PIN_NAME(name,"awid"))
	,awaddr(PIN_NAME(name,"awaddr"))
	,awlen(PIN_NAME(name,"awlen"))
	,awsize(PIN_NAME(name,"awsize"))
	,awready(PIN_NAME(name,"awready")){}


	template<class C> void bind(C& c){
		awvalid(c.awvalid);
		awid(c.awid);
		awaddr(c.awaddr);
		awlen(c.awlen);
		awsize(c.awsize);
		awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type> class amba3_axi_aw_base_target{
public:
	sc_in<bool> awvalid;
	sc_in<typename CFG::id_type> awid;
	sc_in<typename CFG::addr_type> awaddr;
	sc_in<typename CFG::len_type> awlen;
	sc_in<typename CFG::size_type> awsize;
	sc_out<bool> awready;

	amba3_axi_aw_base_target(const char* name=sc_gen_unique_name("amba3_axi_aw_base_target"))
	:awvalid(PIN_NAME(name,"awvalid"))
	,awid(PIN_NAME(name,"awid"))
	,awaddr(PIN_NAME(name,"awaddr"))
	,awlen(PIN_NAME(name,"awlen"))
	,awsize(PIN_NAME(name,"awsize"))
	,awready(PIN_NAME(name,"awready")){}


	template<class C> void bind(C& c){
		awvalid(c.awvalid);
		awid(c.awid);
		awaddr(c.awaddr);
		awlen(c.awlen);
		awsize(c.awsize);
		awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_ar_base_initiator{
public:
	sc_out<bool> arvalid;
	sc_out<typename CFG::id_type> arid;
	sc_out<typename CFG::addr_type> araddr;
	sc_out<typename CFG::len_type> arlen;
	sc_out<typename CFG::size_type> arsize;
	sc_in<bool> arready;

	amba3_axi_ar_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_ar_base_initiator"))
	:arvalid(PIN_NAME(name,"arvalid"))
	,arid(PIN_NAME(name,"arid"))
	,araddr(PIN_NAME(name,"araddr"))
	,arlen(PIN_NAME(name,"arlen"))
	,arsize(PIN_NAME(name,"arsize"))
	,arready(PIN_NAME(name,"arready")){}

	template<class C> void bind(C& c){
		arvalid(c.arvalid);
		arid(c.arid);
		araddr(c.araddr);
		arlen(c.arlen);
		arsize(c.arsize);
		arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_ar_base_target{
public:
	sc_in<bool> arvalid;
	sc_in<typename CFG::id_type> arid;
	sc_in<typename CFG::addr_type> araddr;
	sc_in<typename CFG::len_type> arlen;
	sc_in<typename CFG::size_type> arsize;
	sc_out<bool> arready;

	amba3_axi_ar_base_target(const char* name=sc_gen_unique_name("amba3_axi_ar_base_target"))
	:arvalid(PIN_NAME(name,"arvalid"))
	,arid(PIN_NAME(name,"arid"))
	,araddr(PIN_NAME(name,"araddr"))
	,arlen(PIN_NAME(name,"arlen"))
	,arsize(PIN_NAME(name,"arsize"))
	,arready(PIN_NAME(name,"arready")){}

	template<class C> void bind(C& c){
		arvalid(c.arvalid);
		arid(c.arid);
		araddr(c.araddr);
		arlen(c.arlen);
		arsize(c.arsize);
		arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_base_initiator{
public:
	sc_out<bool> wvalid;
	sc_out<typename CFG::id_type> wid;
	sc_out<bool> wlast;
	sc_out<typename CFG::strb_type> wstrb;
	sc_out<typename CFG::data_type> wdata;
	sc_in<bool> wready;

	amba3_axi_wd_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_wd_base_initiator"))
	:wid(PIN_NAME(name,"wid"))
	,wlast(PIN_NAME(name,"wlast"))
	,wstrb(PIN_NAME(name,"wstrb"))
	,wdata(PIN_NAME(name,"wdata"))
	,wready(PIN_NAME(name,"wready")){}

	template<class C> void bind(C& c){
		wvalid(c.wvalid);
		wid(c.wid);
		wlast(c.wlast);
		wstrb(c.wstrb);
		wdata(c.wdata);
		wready(c.wready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_wd_base_target{
public:
	sc_in<bool> wvalid;
	sc_in<typename CFG::id_type> wid;
	sc_in<bool> wlast;
	sc_in<typename CFG::strb_type> wstrb;
	sc_in<typename CFG::data_type> wdata;

	sc_out<bool> wready;

	amba3_axi_wd_base_target(const char* name=sc_gen_unique_name("amba3_axi_wd_base_target"))
	:wid(PIN_NAME(name,"wid"))
	,wlast(PIN_NAME(name,"wlast"))
	,wstrb(PIN_NAME(name,"wstrb"))
	,wdata(PIN_NAME(name,"wdata"))
	,wready(PIN_NAME(name,"wready")){}

	template<class C> void bind(C& c){
		wvalid(c.wvalid);
		wid(c.wid);
		wlast(c.wlast);
		wstrb(c.wstrb);
		wdata(c.wdata);
		wready(c.wready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};



template<class CFG=amba3_axi_type> class amba3_axi_rd_base_initiator{
public:
	sc_in<bool> rvalid;
	sc_in<typename CFG::id_type> rid;
	sc_in<bool> rlast;
	sc_in<typename CFG::resp_type> rresp;
	sc_in<typename CFG::data_type> rdata;
	sc_out<bool> rready;

	amba3_axi_rd_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_rd_base_initiator"))
	:rvalid(PIN_NAME(name,"rvalid"))
	,rid(PIN_NAME(name,"rid"))
	,rlast(PIN_NAME(name,"rlast"))
	,rresp(PIN_NAME(name,"rresp"))
	,rdata(PIN_NAME(name,"rdata"))
	,rready(PIN_NAME(name,"rready")){}

	template<class C> void bind(C& c){
		rvalid(c.rvalid);
		rid(c.rid);
		rlast(c.rlast);
		rresp(c.rresp);
		rdata(c.rdata);
		rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type> class amba3_axi_rd_base_target{
public:
	sc_out<bool> rvalid;
	sc_out<typename CFG::id_type> rid;
	sc_out<bool> rlast;
	sc_out<typename CFG::resp_type> rresp;
	sc_out<typename CFG::data_type> rdata;
	sc_in<bool> rready;

	amba3_axi_rd_base_target(const char* name=sc_gen_unique_name("amba3_axi_rd_base_target"))
	:rvalid(PIN_NAME(name,"rvalid"))
	,rid(PIN_NAME(name,"rid"))
	,rlast(PIN_NAME(name,"rlast"))
	,rresp(PIN_NAME(name,"rresp"))
	,rdata(PIN_NAME(name,"rdata"))
	,rready(PIN_NAME(name,"rready")){}

	template<class C> void bind(C& c){
		rvalid(c.rvalid);
		rid(c.rid);
		rlast(c.rlast);
		rresp(c.rresp);
		rdata(c.rdata);
		rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_br_base_initiator{
public:
	sc_in<bool> bvalid;
	sc_in<typename CFG::id_type> bid;
	sc_in<typename CFG::resp_type> bresp;
	sc_out<bool> bready;

	amba3_axi_br_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_br_base_initiator")):
	bvalid(PIN_NAME(name,"bvalid"))
	,bid(PIN_NAME(name,"bid"))
	,bresp(PIN_NAME(name,"bresp"))
	,bready(PIN_NAME(name,"bready")){}

	template<class C> void bind(C& c){
		bvalid(c.bvalid);
		bid(c.bid);
		bresp(c.bresp);
		bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type> class amba3_axi_br_base_target{
public:
	sc_out<bool> bvalid;
	sc_out<typename CFG::id_type> bid;
	sc_out<typename CFG::resp_type> bresp;
	sc_in<bool> bready;

	amba3_axi_br_base_target(const char* name=sc_gen_unique_name("amba3_axi_br_base_target")):
	bvalid(PIN_NAME(name,"bvalid"))
	,bid(PIN_NAME(name,"bid"))
	,bresp(PIN_NAME(name,"bresp"))
	,bready(PIN_NAME(name,"bready")){}

	template<class C> void bind(C& c){
		bvalid(c.bvalid);
		bid(c.bid);
		bresp(c.bresp);
		bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_w_base_initiator
:public amba3_axi_aw_base_initiator<CFG>
,public amba3_axi_wd_base_initiator<CFG>
,public amba3_axi_br_base_initiator<CFG>
{
public:
	typedef amba3_axi_aw_base_initiator<CFG> aw_type;
	typedef amba3_axi_wd_base_initiator<CFG> wd_type;
	typedef amba3_axi_br_base_initiator<CFG> br_type;


	amba3_axi_w_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_w_base_initiator"))
	:aw_type(name),wd_type(name),br_type(name){}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_w_base_target
:public amba3_axi_aw_base_target<CFG>
,public amba3_axi_wd_base_target<CFG>
,public amba3_axi_br_base_target<CFG>
{
public:
	typedef amba3_axi_aw_base_target<CFG> aw_type;
	typedef amba3_axi_wd_base_target<CFG> wd_type;
	typedef amba3_axi_br_base_target<CFG> br_type;


	amba3_axi_w_base_target(const char* name=sc_gen_unique_name("amba3_axi_w_base_target"))
	:aw_type(name),wd_type(name),br_type(name){}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type> class amba3_axi_r_base_initiator:public amba3_axi_ar_base_initiator<CFG>, public amba3_axi_rd_base_initiator<CFG>{
public:
	typedef amba3_axi_ar_base_initiator<CFG> ar_type;
	typedef amba3_axi_rd_base_initiator<CFG> rd_type;


	amba3_axi_r_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_r_base_initiator"))
	:ar_type(name),rd_type(name){}

	template<class C> void bind(C& c){
		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_r_base_target:public amba3_axi_ar_base_target<CFG>, public amba3_axi_rd_base_target<CFG>{
public:
	typedef amba3_axi_ar_base_target<CFG> ar_type;
	typedef amba3_axi_rd_base_target<CFG> rd_type;


	amba3_axi_r_base_target(const char* name=sc_gen_unique_name("amba3_axi_r_base_target")):ar_type(name),rd_type(name){}

	template<class C> void bind(C& c){
		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type> class amba3_axi_base_initiator
:public amba3_axi_aw_base_initiator<CFG>
,public amba3_axi_wd_base_initiator<CFG>
,public amba3_axi_br_base_initiator<CFG>
,public amba3_axi_ar_base_initiator<CFG>
,public amba3_axi_rd_base_initiator<CFG>{

public:
	typedef amba3_axi_aw_base_initiator<CFG> aw_type;
	typedef amba3_axi_wd_base_initiator<CFG> wd_type;
	typedef amba3_axi_br_base_initiator<CFG> br_type;
	typedef amba3_axi_ar_base_initiator<CFG> ar_type;
	typedef amba3_axi_rd_base_initiator<CFG> rd_type;


	amba3_axi_base_initiator(const char* name=sc_gen_unique_name("amba3_axi_base_initiator"))
	:aw_type(name),wd_type(name),br_type(name),ar_type(name),rd_type(name){}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);

		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type> class amba3_axi_base_target
:public amba3_axi_aw_base_target<CFG>
,public amba3_axi_wd_base_target<CFG>
,public amba3_axi_br_base_target<CFG>
,public amba3_axi_ar_base_target<CFG>
,public amba3_axi_rd_base_target<CFG>{

public:
	typedef amba3_axi_aw_base_target<CFG> aw_type;
	typedef amba3_axi_wd_base_target<CFG> wd_type;
	typedef amba3_axi_br_base_target<CFG> br_type;
	typedef amba3_axi_ar_base_target<CFG> ar_type;
	typedef amba3_axi_rd_base_target<CFG> rd_type;


	amba3_axi_base_target(const char* name=sc_gen_unique_name("amba3_axi_base_target"))
	:aw_type(name),wd_type(name),br_type(name),ar_type(name),rd_type(name){}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);

		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};



template<class CFG=amba3_axi_type, class BF=NONBUFFERABLE>class amba3_axi_aw_initiator_:public sc_module, public amba3_axi_aw_base_initiator<CFG>, public amba3_axi_aw_initiator_if_<CFG>{
public:
	typedef amba3_axi_aw_initiator_if_<CFG> if_type;
	typedef amba3_axi_aw_base_initiator<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_aw_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_aw_initiator_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void aw_reset(){
		amba3_axi_address_type<CFG> aw = amba3_axi_address_type<CFG>();

		base_type::awvalid.write(false);
		base_type::awid.write(aw.id);
		base_type::awaddr.write(aw.addr);
		base_type::awlen.write(aw.len);
		base_type::awsize.write(aw.size);
	}

	virtual void b_put_aw(const amba3_axi_address_type<CFG>& aw ){
		base_type::awvalid.write(true);
		base_type::awid.write(aw.id);
		base_type::awaddr.write(aw.addr);
		base_type::awlen.write(aw.len);
		base_type::awsize.write(aw.size);
		STALL( base_type::awready.read() == false);
		base_type::awvalid.write(false);
	}

	virtual bool nb_put_aw(const amba3_axi_address_type<CFG>& aw ){
		bool condition = false;

		base_type::awvalid.write(true);
		base_type::awid.write(aw.id);
		base_type::awaddr.write(aw.addr);
		base_type::awlen.write(aw.len);
		base_type::awsize.write(aw.size);
		wait();
		base_type::awvalid.write(false);

		condition = base_type::awready.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::awvalid(c.awvalid);
		base_type::awid(c.awid);
		base_type::awaddr(c.awaddr);
		base_type::awlen(c.awlen);
		base_type::awsize(c.awsize);
		base_type::awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type, class BF=NONBUFFERABLE>class amba3_axi_aw_target_:public sc_module, public amba3_axi_aw_base_target<CFG>, public amba3_axi_aw_target_if_<CFG>{
public:
	typedef amba3_axi_aw_target_if_<CFG> if_type;
	typedef amba3_axi_aw_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_aw_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_aw_target_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void aw_reset(){
		base_type::awready.write(false);
	}

	virtual void b_get_aw( amba3_axi_address_type<CFG>& aw ){
		amba3_axi_address_type<CFG> _aw = amba3_axi_address_type<CFG>();

		base_type::awready.write(true);
		STALL( base_type::awvalid.read() == false);
		base_type::awready.write(false);

		_aw.id = base_type::awid.read();
		_aw.addr = base_type::awaddr.read();
		_aw.len = base_type::awlen.read();
		_aw.size = base_type::awsize.read();

		aw = _aw;
	}

	virtual bool nb_get_aw( amba3_axi_address_type<CFG>& aw ){
		bool condition = false;
		amba3_axi_address_type<CFG> _aw = amba3_axi_address_type<CFG>();

		base_type::awready.write(true);
		wait();
		base_type::awready.write(false);

		_aw.id = base_type::awid.read();
		_aw.addr = base_type::awaddr.read();
		_aw.len = base_type::awlen.read();
		_aw.size = base_type::awsize.read();

		condition = base_type::awvalid.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::awvalid(c.awvalid);
		base_type::awid(c.awid);
		base_type::awaddr(c.awaddr);
		base_type::awlen(c.awlen);
		base_type::awsize(c.awsize);
		base_type::awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type, class BF=NONBUFFERABLE>class amba3_axi_ar_initiator_:public sc_module, public amba3_axi_ar_base_initiator<CFG>, public amba3_axi_ar_initiator_if_<CFG>{
public:
	typedef amba3_axi_ar_initiator_if_<CFG> if_type;
	typedef amba3_axi_ar_base_initiator<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_ar_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_ar_initiator_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void ar_reset(){
		amba3_axi_address_type<CFG> ar = amba3_axi_address_type<CFG>();

		base_type::arvalid.write(false);
		base_type::arid.write(ar.id);
		base_type::araddr.write(ar.addr);
		base_type::arlen.write(ar.len);
		base_type::arsize.write(ar.size);
	}

	virtual void b_put_ar(const amba3_axi_address_type<CFG>& ar ){
		base_type::arvalid.write(true);
		base_type::arid.write(ar.id);
		base_type::araddr.write(ar.addr);
		base_type::arlen.write(ar.len);
		base_type::arsize.write(ar.size);
		STALL( base_type::arready.read() == false);
		base_type::arvalid.write(false);
	}

	virtual bool nb_put_ar(const amba3_axi_address_type<CFG>& ar ){
		bool condition = false;

		base_type::arvalid.write(true);
		base_type::arid.write(ar.id);
		base_type::araddr.write(ar.addr);
		base_type::arlen.write(ar.len);
		base_type::arsize.write(ar.size);
		wait();
		base_type::arvalid.write(false);

		condition = base_type::arready.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::arvalid(c.arvalid);
		base_type::arid(c.arid);
		base_type::araddr(c.araddr);
		base_type::arlen(c.arlen);
		base_type::arsize(c.arsize);
		base_type::arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG=amba3_axi_type, class BF=NONBUFFERABLE>class amba3_axi_ar_target_:public sc_module, public amba3_axi_ar_base_target<CFG>, public amba3_axi_ar_target_if_<CFG>{
public:
	typedef amba3_axi_ar_target_if_<CFG> if_type;
	typedef amba3_axi_ar_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_ar_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_ar_target_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void ar_reset(){
		base_type::arready.write(false);
	}

	virtual void b_get_ar( amba3_axi_address_type<CFG>& ar ){
		amba3_axi_address_type<CFG> _ar = amba3_axi_address_type<CFG>();

		base_type::arready.write(true);
		STALL( base_type::arvalid.read() == false);
		base_type::arready.write(false);

		_ar.id = base_type::arid.read();
		_ar.addr = base_type::araddr.read();
		_ar.len = base_type::arlen.read();
		_ar.size = base_type::arsize.read();

		ar = _ar;
	}

	virtual bool nb_get_ar( amba3_axi_address_type<CFG>& ar ){
		bool condition = false;
		amba3_axi_address_type<CFG> _ar = amba3_axi_address_type<CFG>();

		base_type::arready.write(true);
		wait();
		base_type::arready.write(false);

		_ar.id = base_type::arid.read();
		_ar.addr = base_type::araddr.read();
		_ar.len = base_type::arlen.read();
		_ar.size = base_type::arsize.read();

		condition = base_type::arvalid.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::arvalid(c.arvalid);
		base_type::arid(c.arid);
		base_type::araddr(c.araddr);
		base_type::arlen(c.arlen);
		base_type::arsize(c.arsize);
		base_type::arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE> class amba3_axi_wd_initiator_:public sc_module, public amba3_axi_wd_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_wd_base_initiator<CFG> base_type;
	typedef amba3_axi_wd_type<CFG> data_type;

	SC_HAS_PROCESS(amba3_axi_wd_initiator_);
	amba3_axi_wd_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_wd_initiator_")):sc_module(name),base_type(name){
		end_module();
	}


	virtual void wd_reset(){
		amba3_axi_wd_type<CFG> wd;

		base_type::wvalid.write(false);
		base_type::wid.write(wd.id);
		base_type::wlast.write(wd.last);
		base_type::wstrb.write(wd.strb);
		base_type::wdata.write(wd.data);
	}

	virtual void b_put_wd(const amba3_axi_wd_type<CFG>& wd){

		base_type::wvalid.write(true);
		base_type::wid.write(wd.id);
		base_type::wstrb.write(wd.strb);
		base_type::wdata.write(wd.data);
		base_type::wlast.write(wd.last);
		STALL(base_type::wready.read() == false);
		base_type::wvalid.write(false);

	}

	virtual bool nb_put_wd(const amba3_axi_wd_type<CFG>& wd){
		bool condition = false;

		base_type::wvalid.write(true);
		base_type::wid.write(wd.id);
		base_type::wstrb.write(wd.strb);
		base_type::wdata.write(wd.data);
		base_type::wlast.write(wd.last);
		wait();
		base_type::wvalid.write(false);
		condition = base_type::wready.read();

		return condition;
	}

};


template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE> class amba3_axi_wd_target_:public sc_module, public amba3_axi_wd_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_wd_base_target<CFG> base_type;
	typedef amba3_axi_wd_type<CFG> data_type;

	SC_HAS_PROCESS(amba3_axi_wd_target_);
	amba3_axi_wd_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_wd_target_")):sc_module(name),base_type(name){
		end_module();
	}


	virtual void wd_reset(){
		base_type::wready.write(false);
	}

	virtual void b_get_wd(amba3_axi_wd_type<CFG>& wd){
		amba3_axi_wd_type<CFG> _wd = amba3_axi_wd_type<CFG>();

		base_type::wready.write(true);
		STALL(base_type::wvalid.read() == false);
		base_type::wready.write(false);

		_wd.id = base_type::wid.read();
		_wd.last = base_type::wlast.read();
		_wd.strb = base_type::wstrb.read();
		_wd.data = base_type::wdata.read();

		wd = _wd;
	}

	virtual bool nb_get_wd(amba3_axi_wd_type<CFG>& wd){
		bool condition = false;
		amba3_axi_wd_type<CFG> _wd = amba3_axi_wd_type<CFG>();

		base_type::wready.write(true);
		wait();
		base_type::wready.write(false);

		_wd.id = base_type::wid.read();
		_wd.last = base_type::wlast.read();
		_wd.strb = base_type::wstrb.read();
		_wd.data = base_type::wdata.read();
		wd = _wd;
		condition = base_type::wvalid.read();

		return condition;
	}

};

template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE>
class amba3_axi_rd_initiator_:public sc_module, public amba3_axi_rd_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_rd_base_initiator<CFG> base_type;
	typedef amba3_axi_rd_type<CFG> data_type;

	SC_HAS_PROCESS(amba3_axi_rd_initiator_);
	amba3_axi_rd_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_rd_initiator_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void rd_reset(){
		base_type::rready.write(false);
	}

	virtual void b_get_rd(amba3_axi_rd_type<CFG>& rd){
		data_type _rd = data_type();

		base_type::rready.write(true);
		STALL(base_type::rvalid.read() == false);

		_rd.id = base_type::rid.read();
		_rd.data = base_type::rdata.read();
		_rd.resp = base_type::rresp.read();
		_rd.last = base_type::rlast.read();

		base_type::rready.write(false);
	}

	virtual bool nb_get_rd(amba3_axi_rd_type<CFG>& rd){
		amba3_axi_rd_type<CFG> _rd;

		bool condition = false;

		base_type::rready.write(true);
		wait();
		base_type::rready.write(false);

		_rd.id = base_type::rid.read();
		_rd.data = base_type::rdata.read();
		_rd.resp = base_type::rresp.read();
		_rd.last = base_type::rlast.read();
		condition = base_type::rvalid.read();

		rd = _rd;
		return condition;
	}

	template<class C> void bind(C& c){
		base_type::rvalid(c.rvalid);
		base_type::rid(c.rid);
		base_type::rlast(c.rlast);
		base_type::rresp(c.rresp);
		base_type::rdata(c.rdata);
		base_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};


template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE> class amba3_axi_rd_target_:public sc_module, public amba3_axi_rd_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_rd_base_target<CFG> base_type;
	typedef amba3_axi_rd_type<CFG> data_type;

	SC_HAS_PROCESS(amba3_axi_rd_target_);
	amba3_axi_rd_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_rd_target_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void rd_reset(){
		amba3_axi_rd_type<CFG> rd = amba3_axi_rd_type<CFG>();

		base_type::rvalid.write(false);
		base_type::rid.write(rd.id);
		base_type::rlast.write(rd.last);
		base_type::rresp.write(rd.resp);
		base_type::rdata.write(rd.data);
	}

	virtual void b_put_rd(const amba3_axi_rd_type<CFG>& rd){
		base_type::rid.write(rd.id);
		base_type::rlast.write(rd.last);
		base_type::rresp.write(rd.resp);
		base_type::rdata.write(rd.data);

		base_type::rvalid.write(true);
		STALL(base_type::rready.read() == false);
		base_type::rvalid.write(false);
	}

	virtual bool nb_put_rd(const amba3_axi_rd_type<CFG>& rd){
		amba3_axi_rd_type<CFG> _rd;

		bool condition = false;

		base_type::rid.write(rd.id);
		base_type::rlast.write(rd.last);
		base_type::rresp.write(rd.resp);
		base_type::rdata.write(rd.data);

		base_type::rvalid.write(true);
		wait();
		base_type::rvalid.write(false);

		condition = base_type::rready.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::rvalid(c.rvalid);
		base_type::rid(c.rid);
		base_type::rlast(c.rlast);
		base_type::rresp(c.rresp);
		base_type::rdata(c.rdata);
		base_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}


};

template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE> class amba3_axi_br_initiator_:public sc_module, public amba3_axi_br_base_initiator<CFG>{
public:
	typedef amba3_axi_br_base_initiator<CFG> base_type;
	typedef amba3_axi_resp_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	SC_HAS_PROCESS(amba3_axi_br_initiator_);
	amba3_axi_br_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_br_initiator_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void br_reset(){
		base_type::bready.write(false);
	}

	virtual void b_get_br(amba3_axi_resp_type<CFG>& br){
		base_type::bready.write(true);
		STALL(base_type::bvalid.read() == false);
		br.id = base_type::bid.read();
		br.resp = base_type::bresp.read();

		base_type::bready.write(false);
	}

	virtual bool nb_get_br(amba3_axi_resp_type<CFG>& br){
		bool condition = false;

		base_type::bready.write(true);
		wait();
		br.id = base_type::bid.read();
		br.resp = base_type::bresp.read();
		base_type::bready.write(false);
		condition = base_type::bvalid.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::bvalid(c.bvalid);
		base_type::bid(c.bid);
		base_type::bresp(c.bresp);
		base_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};



template<class CFG=amba3_axi_type,class BF=NONBUFFERABLE> class amba3_axi_br_target_:public sc_module, public amba3_axi_br_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_br_base_target<CFG> base_type;
	typedef amba3_axi_resp_type<CFG> data_type;

	SC_HAS_PROCESS(amba3_axi_br_target_);
	amba3_axi_br_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_br_target_")):sc_module(name),base_type(name){
		end_module();
	}

	virtual void br_reset(){
		amba3_axi_resp_type<CFG> br =  amba3_axi_resp_type<CFG>();

		base_type::bvalid.write(false);
		base_type::bid.write(br.id);
		base_type::bresp.write(br.resp);
	}

	virtual void b_put_br(const amba3_axi_resp_type<CFG>& br){

		base_type::bvalid.write(true);
		base_type::bid.write(br.id);
		base_type::bresp.write(br.resp);
		STALL(base_type::bready.read() == false);
		base_type::bvalid.write(false);

	}

	virtual bool nb_put_br(const amba3_axi_resp_type<CFG>& br){
		bool condition = false;

		base_type::bvalid.write(true);
		base_type::bid.write(br.id);
		base_type::bresp.write(br.resp);
		wait();
		base_type::bvalid.write(false);
		condition = base_type::bready.read();

		return condition;
	}

	template<class C> void bind(C& c){
		base_type::bvalid(c.bvalid);
		base_type::bid(c.bid);
		base_type::bresp(c.bresp);
		base_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG>class amba3_axi_aw_initiator_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_aw_base_initiator<CFG>{
public:
	typedef amba3_axi_aw_base_initiator<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	syn_channel_in<data_type, CFG::AW_FIFO_SIZE, CFG::AW_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_aw_initiator_);
	amba3_axi_aw_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_aw_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void aw_reset(){
		fifo.w_reset();
	}

	virtual void b_put_aw(const amba3_axi_address_type<CFG>& aw ){
		fifo.b_put(aw);
	}

	virtual bool nb_put_aw(const amba3_axi_address_type<CFG>& aw ){
		bool condition = false;
		condition = fifo.nb_put(aw);
		return condition;
	}


	void thread(){
		_aw_reset();
		fifo.r_reset();
		wait();

		while( true ){
			amba3_axi_address_type<CFG> aw;
			fifo.b_get(aw);
			_b_put_awrite(aw);
		}
	}

	virtual void _aw_reset(){
		amba3_axi_address_type<CFG> aw;
		aw.reset();

		base_type::awvalid.write(false);
		base_type::awid.write(aw.id);
		base_type::awaddr.write(aw.addr);
		base_type::awlen.write(aw.len);
		base_type::awsize.write(aw.size);
	}

	virtual void _b_put_aw(const amba3_axi_address_type<CFG>& aw ){
		base_type::awvalid.write(true);
		base_type::awid.write(aw.id);
		base_type::awaddr.write(aw.addr);
		base_type::awlen.write(aw.len);
		base_type::awsize.write(aw.size);
		STALL( base_type::awready.read() == false);
		base_type::awvalid.write(false);
	}

	template<class C> void bind(C& c){
		base_type::awvalid(c.awvalid);
		base_type::awid(c.awid);
		base_type::awaddr(c.awaddr);
		base_type::awlen(c.awlen);
		base_type::awsize(c.awsize);
		base_type::awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG>class amba3_axi_aw_target_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_aw_base_target<CFG>{
public:
	typedef amba3_axi_aw_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	syn_channel_in<data_type, CFG::AW_FIFO_SIZE, CFG::AW_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_aw_target_);
	amba3_axi_aw_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_aw_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void aw_reset(){
		fifo.r_reset();
	}

	virtual void b_get_aw( amba3_axi_address_type<CFG>& aw ){
		fifo.b_get(aw);
	}

	virtual bool nb_get_aw( amba3_axi_address_type<CFG>& aw ){
		bool condition = false;
		condition = fifo.nb_get(aw);
		return condition;
	}

	void thread(){
		_aw_reset();
		fifo.w_reset();
		wait();

		while( true ){
			amba3_axi_address_type<CFG> aw;
			_b_get_awrite(aw);
			fifo.b_put(aw);
		}
	}

	virtual void _aw_reset(){
		base_type::awready.write(false);
	}

	virtual void _b_get_aw( amba3_axi_address_type<CFG>& aw ){
		amba3_axi_address_type<CFG> _aw = amba3_axi_address_type<CFG>();

		base_type::awready.write(true);
		STALL(base_type::awvalid.read() == false);
		base_type::awready.write(false);

		_aw.id = base_type::awid.read();
		_aw.addr = base_type::awaddr.read();
		_aw.len = base_type::awlen.read();
		_aw.size = base_type::awsize.read();
	}

	template<class C> void bind(C& c){
		base_type::awvalid(c.awvalid);
		base_type::awid(c.awid);
		base_type::awaddr(c.awaddr);
		base_type::awlen(c.awlen);
		base_type::awsize(c.awsize);
		base_type::awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG>class amba3_axi_aw_target_<CFG,REGSLICE>:public sc_module, public amba3_axi_aw_base_target<CFG>{
public:
	typedef amba3_axi_aw_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	sc_signal<bool> awvalid_sig;
	sc_signal<data_type> reg_slice;
	sc_signal<bool> awready_sig;

	SC_HAS_PROCESS(amba3_axi_aw_target_);
	amba3_axi_aw_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_aw_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(reg_slice_thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void aw_reset(){
		base_type::awready.write(false);
		awready_sig.write(false);
	}

	virtual void b_get_aw( amba3_axi_address_type<CFG>& aw ){
		base_type::awready.write(true);
		awready_sig.write(true);
		STALL(awvalid_sig.read() == false);
		base_type::awready.write(false);
		awready_sig.write(false);

		aw = reg_slice.read();
	}

	virtual bool nb_get_aw( amba3_axi_address_type<CFG>& aw ){
		bool condition = false;

		base_type::awready.write(true);
		awready_sig.write(true);
		wait();
		base_type::awready.write(false);
		awready_sig.write(false);
		aw = reg_slice.read();
		condition = awvalid_sig.read();

		return condition;
	}

	void reg_slice_thread(){
		amba3_axi_address_type<CFG> aw = amba3_axi_address_type<CFG>();
		awvalid_sig.write(false);
		reg_slice.write(aw);
		wait();

		while( true ){
			aw.reset();

			awvalid_sig.write(base_type::awvalid.read());
			aw.id = base_type::awid.read();
			aw.addr = base_type::awaddr.read();
			aw.len  = base_type::awlen.read();
			aw.size = base_type::awsize.read();

			reg_slice.write(aw);
			wait();
		}
	}

	template<class C> void bind(C& c){
		base_type::awvalid(c.awvalid);
		base_type::awid(c.awid);
		base_type::awaddr(c.awaddr);
		base_type::awlen(c.awlen);
		base_type::awsize(c.awsize);
		base_type::awready(c.awready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG>class amba3_axi_ar_initiator_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_ar_base_initiator<CFG>{
public:
	typedef amba3_axi_ar_base_initiator<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	syn_channel_in<data_type, CFG::AR_FIFO_SIZE, CFG::AR_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_ar_initiator_);
	amba3_axi_ar_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_ar_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void ar_reset(){
		fifo.w_reset();
	}

	virtual void b_put_ar(const amba3_axi_address_type<CFG>& ar ){
		fifo.b_put(ar);
	}

	virtual bool nb_put_ar(const amba3_axi_address_type<CFG>& ar ){
		bool condition = false;
		condition = fifo.nb_put(ar);
		return condition;
	}


	void thread(){
		_ar_reset();
		fifo.r_reset();
		wait();

		while( true ){
			amba3_axi_address_type<CFG> ar;
			fifo.b_get(ar);
			_b_put_ar(ar);
		}
	}

	virtual void _ar_reset(){
		amba3_axi_address_type<CFG> ar;
		ar.reset();

		base_type::arvalid.write(false);
		base_type::arid.write(ar.id);
		base_type::araddr.write(ar.addr);
		base_type::arlen.write(ar.len);
		base_type::arsize.write(ar.size);
	}

	virtual void _b_put_ar(const amba3_axi_address_type<CFG>& ar ){
		base_type::arvalid.write(true);
		base_type::arid.write(ar.id);
		base_type::araddr.write(ar.addr);
		base_type::arlen.write(ar.len);
		base_type::arsize.write(ar.size);
		STALL( base_type::arready.read() == false);
		base_type::arvalid.write(false);
	}

	template<class C> void bind(C& c){
		base_type::arvalid(c.arvalid);
		base_type::arid(c.arid);
		base_type::araddr(c.araddr);
		base_type::arlen(c.arlen);
		base_type::arsize(c.arsize);
		base_type::arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG>class amba3_axi_ar_target_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_ar_base_target<CFG>{
public:
	typedef amba3_axi_ar_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	syn_channel_in<data_type, CFG::ar_FIFO_SIZE, CFG::ar_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_ar_target_);
	amba3_axi_ar_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_ar_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void ar_reset(){
		fifo.r_reset();
	}

	virtual void b_get_ar( amba3_axi_address_type<CFG>& ar ){
		fifo.b_get(ar);
	}

	virtual bool nb_get_ar( amba3_axi_address_type<CFG>& ar ){
		bool condition = false;
		condition = fifo.nb_get(ar);
		return condition;
	}

	void thread(){
		_ar_reset();
		fifo.w_reset();
		wait();

		while( true ){
			amba3_axi_address_type<CFG> ar;
			_b_get_arrite(ar);
			fifo.b_put(ar);
		}
	}

	virtual void _ar_reset(){
		base_type::arready.write(false);
	}

	virtual void _b_get_ar( amba3_axi_address_type<CFG>& ar ){
		amba3_axi_address_type<CFG> _ar = amba3_axi_address_type<CFG>();

		base_type::arready.write(true);
		STALL(base_type::arvalid.read() == false);
		base_type::arready.write(false);

		_ar.id = base_type::arid.read();
		_ar.addr = base_type::araddr.read();
		_ar.len = base_type::arlen.read();
		_ar.size = base_type::arsize.read();
	}

	template<class C> void bind(C& c){
		base_type::arvalid(c.arvalid);
		base_type::arid(c.arid);
		base_type::araddr(c.araddr);
		base_type::arlen(c.arlen);
		base_type::arsize(c.arsize);
		base_type::arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG>class amba3_axi_ar_target_<CFG,REGSLICE>:public sc_module, public amba3_axi_ar_base_target<CFG>{
public:
	typedef amba3_axi_ar_base_target<CFG> base_type;
	typedef amba3_axi_address_type<CFG> data_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	sc_signal<bool> arvalid_sig;
	sc_signal<data_type> reg_slice;
	sc_signal<bool> arready_sig;

	SC_HAS_PROCESS(amba3_axi_ar_target_);
	amba3_axi_ar_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_ar_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(reg_slice_thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void ar_reset(){
		base_type::arready.write(false);
		arready_sig.write(false);
	}

	virtual void b_get_ar( amba3_axi_address_type<CFG>& ar ){
		base_type::arready.write(true);
		arready_sig.write(true);
		STALL(arvalid_sig.read() == false);
		base_type::arready.write(false);
		arready_sig.write(false);

		ar = reg_slice.read();
	}

	virtual bool nb_get_ar( amba3_axi_address_type<CFG>& ar ){
		bool condition = false;

		base_type::arready.write(true);
		arready_sig.write(true);
		wait();
		base_type::arready.write(false);
		arready_sig.write(false);
		ar = reg_slice.read();
		condition = arvalid_sig.read();

		return condition;
	}

	void reg_slice_thread(){
		amba3_axi_address_type<CFG> ar = amba3_axi_address_type<CFG>();
		arvalid_sig.write(false);
		reg_slice.write(ar);
		wait();

		while( true ){
			ar.reset();

			arvalid_sig.write(base_type::arvalid.read());
			ar.id = base_type::arid.read();
			ar.addr = base_type::araddr.read();
			ar.len  = base_type::arlen.read();
			ar.size = base_type::arsize.read();

			reg_slice.write(ar);
			wait();
		}
	}

	template<class C> void bind(C& c){
		base_type::arvalid(c.arvalid);
		base_type::arid(c.arid);
		base_type::araddr(c.araddr);
		base_type::arlen(c.arlen);
		base_type::arsize(c.arsize);
		base_type::arready(c.arready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG> class amba3_axi_wd_initiator_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_wd_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_wd_base_initiator<CFG> base_type;
	typedef amba3_axi_wd_type<CFG> data_type;

	syn_channel_in<data_type, CFG::W_FIFO_SIZE, CFG::W_FIFO_CNT_WIDTH> fifo;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_wd_initiator_);
	amba3_axi_wd_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_wd_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void wd_reset(){
		fifo.w_reset();
	}

	virtual void b_put_wd(const amba3_axi_wd_type<CFG>& wd){
		fifo.b_put(wd);
	}

	virtual bool nb_put_wd(const amba3_axi_wd_type<CFG>& wd){
		bool condition = false;
		condition = fifo.nb_put(wd);
		return condition;
	}

	void thread(){
		fifo.r_reset();
		_wd_reset();
		wait();

		while( true ){
			amba3_axi_wd_type<CFG> wd;
			fifo.b_get(wd);
			_b_put_wd(wd);
		}
	}

	virtual void _wd_reset(){
		amba3_axi_wd_type<CFG> wd;
		wd.reset();

		base_type::wvalid.write(false);
		base_type::wid.write(wd.id);
		base_type::wstrb.write(wd.strb);
		base_type::wdata.write(wd.data);
		base_type::wlast.write(wd.last);
	}

	virtual void _b_put_wd(const amba3_axi_wd_type<CFG>& wd){

		base_type::wvalid.write(true);
		base_type::wid.write(wd.id);
		base_type::wstrb.write(wd.strb);
		base_type::wdata.write(wd.data);
		base_type::wlast.write(wd.last);
		STALL(base_type::wready.read() == false);
		base_type::wvalid.write(false);

	}

	template<class C> void bind(C& c){
		base_type::wvalid(c.wvalid);
		base_type::wid(c.wid);
		base_type::wlast(c.wlast);
		base_type::wstrb(c.wstrb);
		base_type::wdata(c.wdata);
		base_type::wready(c.wready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG> class amba3_axi_wd_target_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_wd_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_wd_base_target<CFG> base_type;
	typedef amba3_axi_wd_type<CFG> data_type;

	syn_channel_in<data_type, CFG::W_FIFO_SIZE, CFG::W_FIFO_CNT_WIDTH> fifo;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_wd_target_);
	amba3_axi_wd_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_wd_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void wd_reset(){
		fifo.r_reset();
	}

	virtual void b_get_wd(amba3_axi_wd_type<CFG>& wd){
		fifo.b_put(wd);
	}

	virtual bool nb_get_wd(amba3_axi_wd_type<CFG>& wd){
		bool condition = false;
		condition = fifo.nb_get(wd);
		return condition;
	}

	void thread(){
		fifo.w_reset();
		_wd_reset();
		wait();

		while( true ){
			amba3_axi_wd_type<CFG> wd;
			_b_get_wd(wd);
			fifo.b_put(wd);
		}
	}

	virtual void _wd_reset(){
		base_type::wready.write(false);
	}

	virtual void _b_get_wd(amba3_axi_wd_type<CFG>& wd){
		amba3_axi_wd_type<CFG> _wd = amba3_axi_wd_type<CFG>();

		base_type::wready.write(true);
		STALL(base_type::awvalid.read() == false);
		base_type::wready.write(false);

		_wd.id = base_type::wid.read();
		_wd.last = base_type::wlast.read();
		_wd.data = base_type::wdata.read();
		_wd.strb = base_type::wstrb.read();

		wd = _wd;
	}

	template<class C> void bind(C& c){
		base_type::wvalid(c.wvalid);
		base_type::wid(c.wid);
		base_type::wlast(c.wlast);
		base_type::wstrb(c.wstrb);
		base_type::wdata(c.wdata);
		base_type::wready(c.wready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG> class amba3_axi_wd_target_<CFG,REGSLICE>:public sc_module, public amba3_axi_wd_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_wd_base_target<CFG> base_type;
	typedef amba3_axi_wd_type<CFG> data_type;

	sc_signal<bool> wvalid_sig;
	sc_signal<data_type> wd_sig;
	sc_signal<bool> wready_sig;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_wd_target_);
	amba3_axi_wd_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_wd_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(reg_slice_thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void wd_reset(){
		wready_sig.write(false);
		base_type::wready.write(false);
	}

	virtual void b_get_wd(amba3_axi_wd_type<CFG>& wd){

		wready_sig.write(false);
		base_type::wready.write(false);
		STALL(wvalid_sig.read() == false);
		wready_sig.write(false);
		base_type::wready.write(false);

		wd = wd_sig.read();

	}

	virtual bool nb_get_wd(amba3_axi_wd_type<CFG>& wd){
		bool condition = false;

		wready_sig.write(false);
		base_type::wready.write(false);
		wait();
		wready_sig.write(false);
		base_type::wready.write(false);

		wd = wd_sig.read();
		condition = wvalid_sig.read();

		return condition;
	}

	void reg_slice_thread(){
		amba3_axi_wd_type<CFG> wd = amba3_axi_wd_type<CFG>();

 		wvalid_sig.write(false);
		wd_sig.write(wd);
 		wait();

		while( true ){

			wvalid_sig.write(base_type::wvalid.read());

			wd.id = base_type::wid.read();
			wd.last = base_type::wlast.read();
			wd.strb = base_type::wstrb.read();
			wd.data = base_type::wdata.read();
			wd_sig.write(wd);

			STALL(wready_sig.read() == false);
		}
	}


	template<class C> void bind(C& c){
		base_type::wvalid(c.wvalid);
		base_type::wid(c.wid);
		base_type::wlast(c.wlast);
		base_type::wstrb(c.wstrb);
		base_type::wdata(c.wdata);
		base_type::wready(c.wready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG> class amba3_axi_rd_initiator_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_rd_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_rd_base_initiator<CFG> base_type;
	typedef amba3_axi_rd_type<CFG> data_type;

	syn_channel_in<data_type, CFG::R_FIFO_SIZE, CFG::R_FIFO_CNT_WIDTH> fifo;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_rd_initiator_);
	amba3_axi_rd_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_rd_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);
		end_module();
	}

	virtual void rd_reset(){
		fifo.r_reset();
	}

	virtual void b_get_rd(data_type& dt){
		fifo.b_get(dt);
	}

	virtual bool nb_get_rd(data_type& dt){
		bool condition = false;
		condition = fifo.b_get(dt);
		return condition;
	}


	void thread(){
		_rd_reset();
		fifo.w_reset();
		wait();

		while( true ){
			data_type dt;
			_b_get_rd(dt);
			fifo.b_put(dt);
		}
	}

	virtual void _rd_reset(){
		base_type::rready.write(false);
	}

	virtual void _b_get_rd(data_type& dt){
		base_type::rready.write(true);
		STALL(base_type::rvalid.read() == false);
		base_type::rready.write(false);

		data_type _dt;
		_dt.id = base_type::rid.read();
		_dt.data = base_type::rdata.read();
		_dt.last = base_type::rlast.read();
		_dt.resp = base_type::rresp.read();

		dt = _dt;
	}

	template<class C> void bind(C& c){
		base_type::rvalid(c.rvalid);
		base_type::rid(c.rid);
		base_type::rlast(c.rlast);
		base_type::rresp(c.rresp);
		base_type::rdata(c.rdata);
		base_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG> class amba3_axi_rd_initiator_<CFG,REGSLICE>:public sc_module, public amba3_axi_rd_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_rd_base_initiator<CFG> base_type;
	typedef amba3_axi_rd_type<CFG> data_type;

	sc_signal<bool> rvalid_sig;
	sc_signal<data_type> reg_slice;
	sc_signal<bool> rready_sig;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_rd_initiator_);
	amba3_axi_rd_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_rd_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(reg_slice_thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void rd_reset(){
		base_type::rready.write(false);
		rready_sig.write(false);
	}

	virtual void b_get_rd(data_type& dt){
		base_type::rready.write(true);
		rready_sig.write(true);
		STALL(rvalid_sig.read() == false);
		base_type::rready.write(false);
		rready_sig.write(false);

		dt = reg_slice.read();
	}

	virtual bool nb_get_rd(data_type& dt){
		bool condition = false;

		base_type::rready.write(true);
		rready_sig.write(true);
		wait();
		base_type::rready.write(false);
		rready_sig.write(false);

		condition = rvalid_sig.read();
		dt = reg_slice.read();

		return condition;
	}

	void reg_slice_thread(){
		data_type d;
		rvalid_sig.write(false);
		reg_slice.write(d);
		wait();

		while( true ){
			rvalid_sig.write(base_type::rvalid.read());

			d.id = base_type::rid.read();
			d.resp = base_type::rresp.read();
			d.last = base_type::rlast.read();
			d.data = base_type::rdata.read();
			reg_slice.write(d);

			STALL( rready_sig.read() == false );
		}
	}

	template<class C> void bind(C& c){
		base_type::rvalid(c.rvalid);
		base_type::rid(c.rid);
		base_type::rlast(c.rlast);
		base_type::rresp(c.rresp);
		base_type::rdata(c.rdata);
		base_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};


template<class CFG>class amba3_axi_rd_target_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_rd_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_rd_base_target<CFG> base_type;
	typedef amba3_axi_rd_type<CFG> data_type;

	syn_channel_in<data_type, CFG::R_FIFO_SIZE, CFG::R_FIFO_CNT_WIDTH> fifo;

	//TODO: Implement methods
	SC_HAS_PROCESS(amba3_axi_rd_target_);
	amba3_axi_rd_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_rd_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);
		end_module();
	}

	virtual void rd_reset(){
		fifo.w_reset();
	}

	virtual void b_put_rd(const data_type& dt){
		fifo.b_put(dt);
	}

	virtual bool nb_put_rd(const data_type& dt){
		bool condition = false;
		condition = fifo.b_put(dt);
		return condition;
	}


	void thread(){
		_rd_reset();
		fifo.r_reset();
		wait();

		while( true ){
			data_type dt;
			fifo.b_get(dt);
			_b_put_rd(dt);
		}
	}

	virtual void _rd_reset(){
		data_type rd = data_type();

		base_type::rvalid.write(false);
		base_type::rid.write(rd.id);
		base_type::rlast.write(rd.last);
		base_type::rresp.write(rd.resp);
		base_type::rdata.write(rd.data);
	}

	virtual void _b_put_rd(const data_type& rd){
		base_type::rvalid.write(true);
		base_type::rid.write(rd.id);
		base_type::rlast.write(rd.last);
		base_type::rresp.write(rd.resp);
		base_type::rdata.write(rd.data);
		STALL(base_type::rready.read() == false);
		base_type::rvalid.write(false);
	}

	template<class C> void bind(C& c){
		base_type::rvalid(c.rvalid);
		base_type::rid(c.rid);
		base_type::rlast(c.rlast);
		base_type::rresp(c.rresp);
		base_type::rdata(c.rdata);
		base_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}

};

template<class CFG>class amba3_axi_br_initiator_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_br_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_br_base_initiator<CFG> base_type;
	typedef amba3_axi_resp_type<CFG> data_type;

	syn_channel_in<data_type, CFG::B_FIFO_SIZE, CFG::B_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_br_initiator_);
	amba3_axi_br_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_br_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void br_reset(){
		fifo.r_reset();
	}

	virtual void b_get_br(data_type& dt){
		fifo.b_get(dt);
	}

	virtual bool nb_get_br(data_type& dt){
		bool condition = false;
		condition = fifo.nb_get(dt);
		return condition;
	}

	void thread(){
		fifo.w_reset();
		_br_reset();
		wait();

		while( true ){
			data_type dt;
			_b_get_br(dt);
			fifo.b_put(dt);
		}
	}

	virtual void _br_reset(){
		base_type::bready.write(false);
	}

	virtual void _b_get_br(data_type& dt){
		base_type::bready.write(true);
		STALL(base_type::bvalid.read() == false);
		base_type::bready.write(false);

		data_type _dt;
		_dt.id = base_type::bid.read();
		_dt.resp = base_type::bresp.read();
		dt = _dt;
	}

	template<class C> void bind(C& c){
		base_type::bvalid(c.bvalid);
		base_type::bid(c.bid);
		base_type::bresp(c.bresp);
		base_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};



template<class CFG> class amba3_axi_br_initiator_<CFG,REGSLICE>:public sc_module, public amba3_axi_br_base_initiator<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_br_base_initiator<CFG> base_type;
	typedef amba3_axi_resp_type<CFG> data_type;

	sc_signal<bool> bvalid_sig;
	sc_signal<data_type> reg_slice;
	sc_signal<bool> bready_sig;

	SC_HAS_PROCESS(amba3_axi_br_initiator_);
	amba3_axi_br_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_br_initiator_")):sc_module(name),base_type(name){
		SC_CTHREAD(reg_slice_thread,clk.pos());
		async_reset_signal_is(nrst,false);
		end_module();
	}

	virtual void br_reset(){
		bready_sig.write(false);
		base_type::bready.write(false);
	}

	virtual void b_get_br(data_type& dt){
		bready_sig.write(false);
		base_type::bready.write(false);
		STALL(bvalid_sig.read() == false);
		bready_sig.write(false);
		base_type::bready.write(false);

		dt = reg_slice.read();
	}

	virtual bool nb_get_br(data_type& dt){
		bool condition = false;

		bready_sig.write(false);
		base_type::bready.write(false);
		wait();
		bready_sig.write(false);
		base_type::bready.write(false);
		condition = bvalid_sig.read();

		dt = reg_slice.read();

		return condition;
	}

	void reg_slice_thread(){
		data_type d;
		d.reset();
		reg_slice.write(d);
		bvalid_sig.write(false);
		wait();

		while( true ){
			bvalid_sig = base_type::bvalid.read();

			d.id = base_type::bid.read();
			d.resp = base_type::bresp.read();
			reg_slice.write(d);

			STALL(bready_sig.read() == false);
		}
	}

	template<class C> void bind(C& c){
		base_type::bvalid(c.bvalid);
		base_type::bid(c.bid);
		base_type::bresp(c.bresp);
		base_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG> class amba3_axi_br_target_<CFG,BUFFERABLE>:public sc_module, public amba3_axi_br_base_target<CFG>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	typedef amba3_axi_br_base_target<CFG> base_type;
	typedef amba3_axi_resp_type<CFG> data_type;

	syn_channel_in<data_type, CFG::B_FIFO_SIZE, CFG::B_FIFO_CNT_WIDTH> fifo;

	SC_HAS_PROCESS(amba3_axi_br_target_);
	amba3_axi_br_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_br_target_")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	virtual void br_reset(){
		fifo.w_reset();
	}

	virtual void b_put_br(const data_type& dt){
		fifo.b_put(dt);
	}

	virtual bool nb_put_br(const data_type& dt){
		bool condition = false;
		condition = fifo.nb_put(dt);
		return condition;
	}

	void thread(){
		fifo.r_reset();
		_br_reset();
		wait();

		while( true ){
			data_type dt;
			fifo.b_get(dt);
			_b_put_br(dt);
		}
	}

	virtual void _br_reset(){
		data_type br = data_type();
		br.reset();

		base_type::bvalid.write(false);
		base_type::bid.write(br.id);
		base_type::bresp.write(br.resp);
	}

	virtual void _b_put_br(const data_type& dt){
		base_type::bid.write(dt.id);
		base_type::bresp.write(dt.resp);

		base_type::bvalid.write(true);
		STALL(base_type::bready.read() == false);
		base_type::bvalid.write(false);
	}

	template<class C> void bind(C& c){
		base_type::bvalid(c.bvalid);
		base_type::bid(c.bid);
		base_type::bresp(c.bresp);
		base_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type, class AW_BF=NONBUFFERABLE, class WD_BF=NONBUFFERABLE, class BR_BF=NONBUFFERABLE>
class amba3_axi_w_initiator_:
public amba3_axi_aw_initiator_<CFG,AW_BF>
,public amba3_axi_wd_initiator_<CFG,WD_BF>
,public amba3_axi_br_initiator_<CFG,BR_BF>{
public:
	typedef amba3_axi_aw_base_initiator<CFG> aw_type;
	typedef amba3_axi_wd_base_initiator<CFG> wd_type;
	typedef amba3_axi_br_base_initiator<CFG> br_type;


	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_w_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_w_initiator_"))
	:amba3_axi_aw_initiator_<CFG,AW_BF>(name),amba3_axi_wd_initiator_<CFG,WD_BF>(name),amba3_axi_br_initiator_<CFG,BR_BF>(name){
		amba3_axi_aw_initiator_<CFG,AW_BF>::clk(clk);
		amba3_axi_wd_initiator_<CFG,WD_BF>::clk(clk);
		amba3_axi_br_initiator_<CFG,BR_BF>::clk(clk);

		amba3_axi_aw_initiator_<CFG,AW_BF>::nrst(nrst);
		amba3_axi_wd_initiator_<CFG,WD_BF>::nrst(nrst);
		amba3_axi_br_initiator_<CFG,BR_BF>::nrst(nrst);

		sc_module::end_module();
	}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type, class AW_BF=NONBUFFERABLE, class WD_BF=NONBUFFERABLE, class BR_BF=NONBUFFERABLE>
class amba3_axi_w_target_:public amba3_axi_aw_target_<CFG,AW_BF>,public amba3_axi_wd_target_<CFG,WD_BF>,public amba3_axi_br_target_<CFG,BR_BF>{
public:
	typedef amba3_axi_aw_base_target<CFG> aw_type;
	typedef amba3_axi_wd_base_target<CFG> wd_type;
	typedef amba3_axi_br_base_target<CFG> br_type;


	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_w_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_w_target_"))
	:amba3_axi_aw_target_<CFG,AW_BF>(name),amba3_axi_wd_target_<CFG,WD_BF>(name),amba3_axi_br_target_<CFG,BR_BF>(name){
		amba3_axi_aw_initiator_<CFG,AW_BF>::clk(clk);
		amba3_axi_wd_initiator_<CFG,WD_BF>::clk(clk);
		amba3_axi_br_initiator_<CFG,BR_BF>::clk(clk);

		amba3_axi_aw_initiator_<CFG,AW_BF>::nrst(nrst);
		amba3_axi_wd_initiator_<CFG,WD_BF>::nrst(nrst);
		amba3_axi_br_initiator_<CFG,BR_BF>::nrst(nrst);

		sc_module::end_module();
	}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type,class AR_BF=NONBUFFERABLE, class RD_BF=NONBUFFERABLE>
class amba3_axi_r_initiator_:
public amba3_axi_ar_initiator_<CFG,AR_BF>
,public amba3_axi_rd_initiator_<CFG,RD_BF>{
public:
	typedef amba3_axi_ar_base_initiator<CFG> ar_type;
	typedef amba3_axi_rd_base_initiator<CFG> rd_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	SC_HAS_PROCESS(amba3_axi_r_initiator_);

	amba3_axi_r_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_r_initiator_"))
	:amba3_axi_ar_initiator_<CFG,AR_BF>(name),amba3_axi_rd_initiator_<CFG,RD_BF>(name){
		amba3_axi_ar_initiator_<CFG,AR_BF>::clk(clk);
		amba3_axi_rd_initiator_<CFG,RD_BF>::clk(clk);

		amba3_axi_ar_initiator_<CFG,AR_BF>::nrst(nrst);
		amba3_axi_rd_initiator_<CFG,RD_BF>::nrst(nrst);

		//end_module();
	}

	template<class C> void bind(C& c){
		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type,class AR_BF=NONBUFFERABLE, class RD_BF=NONBUFFERABLE>
class amba3_axi_r_target_:
public amba3_axi_ar_target_<CFG,AR_BF>
,public amba3_axi_rd_target_<CFG,RD_BF>{

public:
	typedef amba3_axi_ar_base_target<CFG> ar_type;
	typedef amba3_axi_rd_base_target<CFG> rd_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	SC_HAS_PROCESS(amba3_axi_r_target_);

	amba3_axi_r_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_r_target_"))
	:amba3_axi_ar_target_<CFG,AR_BF>(name),amba3_axi_rd_target_<CFG,RD_BF>(name){
		amba3_axi_ar_initiator_<CFG,AR_BF>::clk(clk);
		amba3_axi_rd_initiator_<CFG,RD_BF>::clk(clk);

		amba3_axi_ar_initiator_<CFG,AR_BF>::nrst(nrst);
		amba3_axi_rd_initiator_<CFG,RD_BF>::nrst(nrst);


		sc_module::end_module();
	}

	template<class C> void bind(C& c){
		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=amba3_axi_type, class AW_BF=NONBUFFERABLE, class WD_BF=NONBUFFERABLE, class BR_BF=NONBUFFERABLE, class AR_BF=NONBUFFERABLE, class RD_BF=NONBUFFERABLE>
class amba3_axi_initiator_:
public amba3_axi_aw_initiator_<CFG,AW_BF>
,public amba3_axi_wd_initiator_<CFG,WD_BF>
,public amba3_axi_br_initiator_<CFG,BR_BF>
,public amba3_axi_ar_initiator_<CFG,AR_BF>
,public amba3_axi_rd_initiator_<CFG,RD_BF>{
public:
	typedef amba3_axi_aw_base_initiator<CFG> aw_type;
	typedef amba3_axi_wd_base_initiator<CFG> wd_type;
	typedef amba3_axi_br_base_initiator<CFG> br_type;
	typedef amba3_axi_ar_base_initiator<CFG> ar_type;
	typedef amba3_axi_rd_base_initiator<CFG> rd_type;


	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_initiator_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_initiator_"))
	:amba3_axi_aw_initiator_<CFG,AW_BF>(name)
	 ,amba3_axi_wd_initiator_<CFG,WD_BF>(name)
	 ,amba3_axi_br_initiator_<CFG,BR_BF>(name)
	 ,amba3_axi_ar_initiator_<CFG,AR_BF>(name)
	 ,amba3_axi_rd_initiator_<CFG,RD_BF>(name){

		amba3_axi_aw_initiator_<CFG,AW_BF>::clk(clk);
		amba3_axi_ar_initiator_<CFG,AR_BF>::clk(clk);
		amba3_axi_wd_initiator_<CFG,WD_BF>::clk(clk);
		amba3_axi_rd_initiator_<CFG,RD_BF>::clk(clk);
		amba3_axi_br_initiator_<CFG,BR_BF>::clk(clk);

		amba3_axi_aw_initiator_<CFG,AW_BF>::nrst(nrst);
		amba3_axi_ar_initiator_<CFG,AR_BF>::nrst(nrst);
		amba3_axi_wd_initiator_<CFG,WD_BF>::nrst(nrst);
		amba3_axi_rd_initiator_<CFG,RD_BF>::nrst(nrst);
		amba3_axi_br_initiator_<CFG,BR_BF>::nrst(nrst);

		//sc_module::end_module();
	}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);

		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=amba3_axi_type, class AW_BF=NONBUFFERABLE, class WD_BF=NONBUFFERABLE, class BR_BF=NONBUFFERABLE, class AR_BF=NONBUFFERABLE, class RD_BF=NONBUFFERABLE>
class amba3_axi_target_:public amba3_axi_aw_target_<CFG,AW_BF>,public amba3_axi_wd_target_<CFG,WD_BF>,public amba3_axi_br_target_<CFG,BR_BF>,public amba3_axi_ar_target_<CFG,AR_BF>,public amba3_axi_rd_target_<CFG,RD_BF>{
public:
	typedef amba3_axi_aw_base_target<CFG> aw_type;
	typedef amba3_axi_wd_base_target<CFG> wd_type;
	typedef amba3_axi_br_base_target<CFG> br_type;
	typedef amba3_axi_ar_base_target<CFG> ar_type;
	typedef amba3_axi_rd_base_target<CFG> rd_type;


	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_target_(const sc_module_name& name=sc_gen_unique_name("amba3_axi_target_"))
	:amba3_axi_aw_target_<CFG,AW_BF>(name)
	 ,amba3_axi_wd_target_<CFG,WD_BF>(name)
	 ,amba3_axi_br_target_<CFG,BR_BF>(name)
	 ,amba3_axi_ar_target_<CFG,AR_BF>(name)
	 ,amba3_axi_rd_target_<CFG,RD_BF>(name)
	 {


		amba3_axi_aw_target_<CFG,AW_BF>::clk(clk);
		amba3_axi_ar_target_<CFG,AR_BF>::clk(clk);
		amba3_axi_wd_target_<CFG,WD_BF>::clk(clk);
		amba3_axi_rd_target_<CFG,RD_BF>::clk(clk);
		amba3_axi_br_target_<CFG,BR_BF>::clk(clk);

		amba3_axi_aw_target_<CFG,AW_BF>::nrst(nrst);
		amba3_axi_ar_target_<CFG,AR_BF>::nrst(nrst);
		amba3_axi_wd_target_<CFG,WD_BF>::nrst(nrst);
		amba3_axi_rd_target_<CFG,RD_BF>::nrst(nrst);
		amba3_axi_br_target_<CFG,BR_BF>::nrst(nrst);

//		sc_moule::end_module();
	}

	template<class C> void bind(C& c){
		aw_type::awvalid(c.awvalid);
		aw_type::awid(c.awid);
		aw_type::awaddr(c.awaddr);
		aw_type::awlen(c.awlen);
		aw_type::awsize(c.awsize);
		aw_type::awready(c.awready);

		wd_type::wvalid(c.wvalid);
		wd_type::wid(c.wid);
		wd_type::wlast(c.wlast);
		wd_type::wstrb(c.wstrb);
		wd_type::wdata(c.wdata);
		wd_type::wready(c.wready);

		br_type::bvalid(c.bvalid);
		br_type::bid(c.bid);
		br_type::bresp(c.bresp);
		br_type::bready(c.bready);

		ar_type::arvalid(c.arvalid);
		ar_type::arid(c.arid);
		ar_type::araddr(c.araddr);
		ar_type::arlen(c.arlen);
		ar_type::arsize(c.arsize);
		ar_type::arready(c.arready);

		rd_type::rvalid(c.rvalid);
		rd_type::rid(c.rid);
		rd_type::rlast(c.rlast);
		rd_type::rresp(c.rresp);
		rd_type::rdata(c.rdata);
		rd_type::rready(c.rready);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};
#endif /* AMBA3_AXI_IF_H_ */
