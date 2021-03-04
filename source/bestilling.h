
enum bestillingsType{opp, inn, ned};

struct bestilling
{
    int etasje;                 // Etasje heisen skal til
    enum bestillingsType type;  // Knapptypen, enten er knappen fra heispanelet, eller så er det utenfra med et ønske om enten opp eller ned

};

struct bestilling bestillingsKo[10] = { 0 };

void o_lookForOrders();

void o_leggTilBestilling(struct bestilling nyBestilling);

bool o_bestillingFraHeispanel(struct bestilling panelBestilling);

int o_returnSizeOfOrders();

bool o_orderFound();

int o_returnNextOrder(bool* mother_orderDone);      // Funksjon skal bare brukes hvis det finnes en bestilling

void o_checkIfOrderisInLine(struct bestilling order);

void o_findPriority(struct bestilling order);

void o_checkDir(struct bestilling order);

void pushArrayBack();

void pushArray();