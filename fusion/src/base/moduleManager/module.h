#ifndef MODULE_HEADER
#define MODULE_HEADER


class module {
public:
	int bind;
	bool Enabled;
	virtual void Update() = 0;
	virtual void RenderUpdate() = 0;
	virtual void PacketRecieve() = 0;
	virtual void RenderMenu() = 0;

};

#endif

