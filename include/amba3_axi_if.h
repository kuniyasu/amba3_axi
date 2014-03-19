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

class PIN{};
class TLM2LT{};
class TLM2AT{};

#define TR_NAME(_name) (std::string(name())+"_"+std::string(_name)).c_str()
#define PIN_NAME(bname,_name_) (std::string(bname)+"_"+std::string(_name_)).c_str()

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

};

class amba3_axi_address_type:public amba3_axi_type{
public:
	id_type id;
	addr_type addr;
	len_type len;
	size_type size;

	amba3_axi_address_type(){
		reset();
	}

	amba3_axi_address_type(const amba3_axi_address_type dt){
		this->id = dt.id;
		this->addr = dt.addr;
		this->len = dt.len;
		this->size = dt.size;
	}

	void reset(){}

};

class amba3_axi_wd_type:public amba3_axi_type{
public:
	id_type id;
	bool last;
	strb_type strb;
	data_type data;

	amba3_axi_wd_type(){
		reset();
	}

	amba3_axi_wd_type(const amba3_axi_wd_type dt){
		this->id = dt.id;
		this->last = dt.last;
		this->strb = dt.strb;
		this->data = dt.data;
	}

	void reset(){}

};

class amba3_axi_rd_type:public amba3_axi_type{
public:
	id_type id;
	bool last;
	resp_type resp;
	data_type data;

	amba3_axi_rd_type(){
		reset();
	}

	amba3_axi_rd_type(const amba3_axi_rd_type dt){
		this->id = dt.id;
		this->last = dt.last;
		this->resp = dt.resp;
		this->data = dt.data;
	}

	void reset(){}
};

class amba3_axi_resp_type:public amba3_axi_type{
public:
	id_type id;
	resp_type resp;

	amba3_axi_resp_type(){
		reset();
	}

	amba3_axi_resp_type(const amba3_axi_resp_type dt){
		this->id = dt.id;
		this->resp = dt.resp;
	}

	void reset(){}
};


class amba3_axi_if:public sc_interface {
public:
	virtual void write_axi_command() = 0;
	virtual void read_axi_command() = 0;

};


class amba3_axi_aw_sig:public amba3_axi_type{
public:
	sc_signal<bool> awvalid;
	sc_signal<id_type> awid;
	sc_signal<addr_type> awaddr;
	sc_signal<len_type> awlen;
	sc_signal<size_type> awsize;
	sc_signal<bool> awready;
};

class amba3_axi_ar_sig:public amba3_axi_type{
public:
	sc_signal<bool> arvalid;
	sc_signal<id_type> arid;
	sc_signal<addr_type> araddr;
	sc_signal<len_type> arlen;
	sc_signal<size_type> arsize;
	sc_signal<bool> arready;
};

class amba3_axi_wd_sig:public amba3_axi_type{
public:
	sc_signal<bool> wvalid;
	sc_signal<id_type> wid;
	sc_signal<bool> wlast;
	sc_signal<strb_type> wstrb;
	sc_signal<data_type> wdata;
	sc_signal<bool> wready;
};

class amba3_axi_rd_sig:public amba3_axi_type{
public:
	sc_signal<bool> rvalid;
	sc_signal<id_type> rid;
	sc_signal<bool> rlast;
	sc_signal<resp_type> rresp;
	sc_signal<data_type> rdata;
	sc_signal<bool> rready;
};

class amba3_axi_br_sig:public amba3_axi_type{
public:
	sc_signal<bool> bvalid;
	sc_signal<id_type> bid;
	sc_signal<bool> bready;
};

class amba3_axi_sig:public amba3_axi_type{
public:
	sc_signal<bool> awvalid;
	sc_signal<id_type> awid;
	sc_signal<bool> awready;

	sc_signal<bool> arvalid;
	sc_signal<id_type> arid;
	sc_signal<bool> arready;

	sc_signal<bool> wvalid;
	sc_signal<id_type> wid;
	sc_signal<bool> wready;

	sc_signal<bool> rvalid;
	sc_signal<id_type> rid;
	sc_signal<bool> rready;

	sc_signal<bool> bvalid;
	sc_signal<id_type> bid;
	sc_signal<bool> bready;
};



#endif /* AMBA3_AXI_IF_H_ */
