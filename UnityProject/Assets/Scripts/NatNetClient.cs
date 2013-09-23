using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Net;

public class NatNetClient : MonoBehaviour {

	public string serverIP;
	public IntPtr self;
	// Use this for initialization
	void Start () {
		self = natnetclient_init();
		UInt32 addr = BitConverter.ToUInt32(IPAddress.Parse(serverIP).GetAddressBytes(), 0);
		Debug.Log(addr);
		natnetclient_ping(self, addr);
	}
	void Destroy () {
		natnetclient_destroy(self);
	}
	
	// Update is called once per frame
	void Update () {
		natnetclient_process_frame(self);
	}
	
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern IntPtr natnetclient_init();
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_destroy(IntPtr self);
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_ping(IntPtr self, UInt32 host);
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_process_frame(IntPtr self);
}
