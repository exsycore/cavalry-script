<div align="center">

```
 ██████╗ █████╗ ██╗   ██╗ █████╗ ██╗     ██████╗ ██╗   ██╗
██╔════╝██╔══██╗██║   ██║██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝
██║     ███████║██║   ██║███████║██║     ██████╔╝ ╚████╔╝ 
██║     ██╔══██║╚██╗ ██╔╝██╔══██║██║     ██╔══██╗  ╚██╔╝  
╚██████╗██║  ██║ ╚████╔╝ ██║  ██║███████╗██║  ██║   ██║   
 ╚═════╝╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝  
```

**SA:MP Roleplay Gamemode Script**

![SA:MP](https://img.shields.io/badge/SA%3AMP-0.3.7-red?style=for-the-badge&logo=data:image/png;base64,iVBORw0KGgo=)
![Language](https://img.shields.io/badge/Language-Pawn-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-Private-black?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge)

</div>

---

## 📋 สารบัญ

- [เกี่ยวกับโปรเจค](#-เกี่ยวกับโปรเจค)
- [Dependencies](#-dependencies)
- [ระบบที่มีในเซิร์ฟเวอร์](#-ระบบที่มีในเซิร์ฟเวอร์)
- [การติดตั้ง](#-การติดตั้ง)
- [ทีมพัฒนา](#-ทีมพัฒนา)

---

## 🎮 เกี่ยวกับโปรเจค

**Cavalry Script** คือ Gamemode สำหรับเซิร์ฟเวอร์ SA:MP แนว Roleplay  
พัฒนาด้วยภาษา Pawn โดยใช้ระบบ YSI และ MySQL เป็นฐาน

---

## 📦 Dependencies

| Library | รายละเอียด |
|---|---|
| [YSI](https://github.com/pawn-lang/YSI-Includes) | Hooks, Iterators, Inline callbacks |
| [mysql-plugin](https://github.com/pBlueG/SA-MP-MySQL) | ระบบฐานข้อมูล MySQL |
| [sscanf2](https://github.com/Y-Less/sscanf) | Parse command parameters |
| [streamer](https://github.com/samp-incognito/samp-streamer-plugin) | Dynamic objects / areas |

---

## ⚙️ ระบบที่มีในเซิร์ฟเวอร์

### 🚗 ระบบยานพาหนะ
- [x] ซื้อ/ขายรถ (Dealership)
- [x] เรียกรถ / เก็บรถ / กู้คืนรถ
- [x] ล็อก / ปลดล็อกรถ
- [x] เปลี่ยนป้ายทะเบียน
- [x] บันทึก Mods / สีรถ
- [x] สตาร์ท / ดับเครื่องยนต์

### 👤 ระบบผู้เล่น
- [ ] ระบบลงทะเบียน / เข้าสู่ระบบ
- [ ] ระบบตัวละคร
- [ ] ระบบ Inventory
- [ ] ระบบสกิล / Stat

### 💼 ระบบอาชีพ
- [ ] <!-- ใส่อาชีพที่มีในเซิร์ฟ -->
- [ ] <!-- ใส่อาชีพที่มีในเซิร์ฟ -->
- [ ] <!-- ใส่อาชีพที่มีในเซิร์ฟ -->

### 🏢 ระบบองค์กร / แก๊ง
- [ ] <!-- ใส่ระบบองค์กรที่มีในเซิร์ฟ -->
- [ ] <!-- ใส่ระบบแก๊งที่มีในเซิร์ฟ -->

### 🏠 ระบบอสังหาริมทรัพย์
- [ ] ซื้อ/ขายบ้าน
- [ ] ซื้อ/ขายธุรกิจ

### 💰 ระบบเศรษฐกิจ
- [ ] ระบบธนาคาร
- [ ] ระบบ ATM
- [ ] <!-- ใส่ระบบเศรษฐกิจที่มีในเซิร์ฟ -->

### 🛠️ ระบบ Admin
- [x] จัดการ Vehicle Spots (Spawn / Store / Recover)
- [ ] <!-- ใส่ระบบ admin เพิ่มเติม -->

---

## 🚀 การติดตั้ง

```bash
# 1. Clone โปรเจค
git clone https://github.com/exsycore/cavalry-script.git

# 3. แก้ไขค่าใน config
nano gamemodes/config.inc

# 4. Compile และรัน
samp-server
```

### ⚙️ ตั้งค่า Database (`mysql.ini`)

```pawn
#define DB_HOST     "localhost"
#define DB_USER     "root"
#define DB_PASS     "root"
#define DB_NAME     "sampsvr"
```

---

## 👥 ทีมพัฒนา

| ชื่อ | บทบาท |
|---|---|
| exsycore | Lead Developer |
| MeenCore | Developer |

---

<div align="center">

**Cavalry Script** © 2025 — Private Repository

</div>
