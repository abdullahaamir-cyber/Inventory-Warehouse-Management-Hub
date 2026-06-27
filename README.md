# 📦 Advanced Inventory & Warehouse Management Hub

An interactive inventory database tracking utility designed to classify, organize, and calculate storage configurations for multi-branch retail product lines. Built from scratch using native object-oriented frameworks, the system seamlessly logs categorized consumer merchandise pipelines while prioritizing data stability through automated system state updates.

---

## 🕹️ Key Features

* **Multi-Tier Product Classification:** Tracks catalog inventories utilizing specialized product frameworks including:
  * 👕 **Clothing Matrix:** Dedicated sizing, materials, and retail fashion classifications.
  * ⚡ **Electronic Frameworks:** Houses delicate item tracking modules alongside advanced safety controls (`FragileElectronics`).
  * 🍎 **Grocery Ecosystems:** Incorporates tracking parameters optimized for handling delicate consumer inventories (`Perishable` vs. `NonPerishable`).
* **Automated File Persistence:** Scans and initializes all supplier data records directly on system launch and safely exports structural ledger sheets upon program termination.
* **Streamlined UI Control Loop:** Uses modern terminal encoding wrappers (such as UTF-8 adjustments and ANSI clear functions) to draw intuitive operational menu dashboards.
* **Fault-Tolerant Asset Logs:** Features operational data checks safeguarding input fields against accidental catalog corruption during edits.

---

## 📂 Project Architecture Reference

Based on the core workspace structure, the build features decentralized product modules:
```text
├── main.cpp                  # Primary Controller Initialization Lifecycle
├── Product.h/.cpp            # Main Base Item Blueprint Matrix
├── ClothingProduct.h/.cpp    # Apparels Logging Framework
├── ElectronicProduct.h/.cpp  # Electronics Hardware Configuration Layer
├── FragileElectronics.h/.cpp # Delicate Hardware Structural Overrides
├── GroceryProduct.h/.cpp     # Food & Utility Supply Logic 
├── PerishableGrocery.h/.cpp  # Controlled Lifetime Storage Audits
└── NonPerishable.h/.cpp      # Stable Storage Asset Handling
