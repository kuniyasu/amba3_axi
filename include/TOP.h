/*
 * TOP.h
 *
 *  Created on: 2014/01/04
 *      Author: Kuniyasu
 */

#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "amba3_axi_if.h"

class Producer:public sc_module{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	amba3_axi_address_type a;
//	syn_fifo_3<sc_uint<4> >::put put_if;

	SC_HAS_PROCESS(Producer);
	Producer(const sc_module_name name):sc_module(name){
		cout << "Instanced." << endl;

		SC_CTHREAD(thread,clk.pos());
		reset_signal_is(nrst,false);

		end_module();
	}

	void thread(){
//		put_if.w_reset();
		wait();

		while( true ){
			for(int i=0; i<10; i++){
				cout << "PUT data" << i << endl;
//				put_if.b_put(i);
				//wait();
			}
			wait();
		}
	}
};

class Consumer:public sc_module{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

//	syn_fifo_3<sc_uint<4> >::get get_if;

	SC_HAS_PROCESS(Consumer);
	Consumer(const sc_module_name name):sc_module(name){
		cout << "Instanced." << endl;
		SC_CTHREAD(thread,clk.pos());
		reset_signal_is(nrst,false);
		end_module();
	}

	void thread(){
//		get_if.r_reset();
		wait();

		sc_uint<4> data;

		while( true ){
			for(int i=0; i<10; i++){
//				get_if.b_get(data);
				cout << "GET data" << data << endl;
				//wait();
			}

			wait();
		}
	}

};


class TOP:public sc_module{
public:
	sc_clock clk;
	sc_signal<bool> nrst;
	Producer producer;
	Consumer consumer;
//	syn_fifo_3<sc_uint<4> >::channel chain;

	SC_HAS_PROCESS(TOP);

	TOP(const sc_module_name name):sc_module(name)
	,clk("CLK", 25, SC_NS, 0.5, 5, SC_NS, true )
	,nrst("nrst")
	,producer("producer")
	,consumer("consumer")
	//,chain("chain")
	{

		producer.clk(clk);
		producer.nrst(nrst);
//		producer.put_if.bind(chain);

		consumer.clk(clk);
		consumer.nrst(nrst);
//		consumer.get_if.bind(chain);

		SC_THREAD(timeout_thread);
		end_module();
	}

	void timeout_thread(){
		nrst = false;
		wait(100,SC_NS);

		nrst = true;
		wait(100,SC_MS);

		cout << "Simulation timeout." << endl;
		sc_stop();
	}
};


#endif /* TOP_H_ */
