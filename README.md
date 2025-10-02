# ระบบการจัดการข้อมูลสัมมนาผู้บริหาร



**ระบบจัดการข้อมูลการสัมมนาผู้บริหาร ช่วยวางแผนการใช้ห้องสัมมนาในบริษัท
เพื่อป้องกันการทับซ้อนของสัมมนาและเพิ่มประสิทธิภาพการจัดงาน**



## Main Features

# Seminar Management System

## 🔹 Login System
ก่อนเข้าถึงระบบ ผู้ใช้ต้อง **Log in** เพื่อกำหนดสิทธิ์ผู้ใช้งาน ระบบแบ่งออกเป็น **5 ระดับ**  

---

## 1️⃣ Admin (ผู้ดูแลระบบสูงสุด)
**หน้าที่หลัก:**  
- กำหนดสิทธิ์ผู้ใช้งานในระบบ (User Roles / Permission)  
- ตรวจสอบการสำรองข้อมูล / Backup  
- Export รายงานรวมทั้งบริษัท  
- กำหนดห้องสัมมนาและ capacity สูงสุด  


---

## 2️⃣ Organizer (ผู้จัดงาน)
**หน้าที่หลัก:**  
- เพิ่ม / แก้ไข / ลบ / ค้นหาสัมมนา  
- จัดตารางวัน เวลา วิทยากร และห้องสัมมนา  
- เพิ่ม / แก้ไข / ลบ / ค้นหาผู้เข้าร่วม  
- อนุมัติการเข้าร่วม (Approve)  
- ดูรายงานสรุปผลรายวันหรือรายสัมมนา  

---

## 3️⃣ Speaker (วิทยากร / ผู้บรรยาย)
**หน้าที่:**  
- ดูรายละเอียดสัมมนาที่ตัวเองบรรยาย  
- ดูรายชื่อผู้เข้าร่วมของตัวเอง  
- อัปโหลดไฟล์สไลด์ประกอบการบรรยาย  
- ดู Feedback ของตัวเอง  

---

## 4️⃣ Participant (ผู้เข้าร่วมสัมมนา)
**หน้าที่:**  
- ลงทะเบียนเข้าร่วมสัมมนา  
- ดูตารางสัมมนาที่เข้าร่วม  
- ให้ Feedback หลังสัมมนา  
- ดาวน์โหลดเอกสาร / สไลด์  

---

## 5️⃣ Viewer (ผู้ดูข้อมูลสาธารณะ)
**หน้าที่:**  
- ดูตารางสัมมนาและรายละเอียดสาธารณะ  
- ไม่สามารถแก้ไขหรือบันทึกข้อมูลใด ๆ  

---

## 💡 Workflow (ภาพรวม)
1. **Participant** ลงทะเบียน → Submit  
2. **Organizer** ตรวจสอบและ Approve → Update status approved  
3. **Organizer** จัดตาราง / เลือกวิทยากร / จัดห้อง  
4. **Check-in วันงาน**  
   - Onsite → Organizer / Staff เช็คชื่อ  
   - Online → ตรวจสอบการเข้าถึง link / token  
5. **Feedback** → Participant ส่งหลังสัมมนา  
6. **รายงานสรุป** → Organizer สรุปและเก็บในระบบ  
7. **Admin** ควบคุมระบบ, Backup, Export รายงานรวมทั้งบริษัท  

---

## 📊 Permission Matrix (ตารางสิทธิ์)

| Feature / Role               | Admin | Organizer | Speaker | Participant | Viewer |
|-------------------------------|:-----:|:---------:|:-------:|:-----------:|:------:|
| Add / Edit / Delete Seminar   | ❌    | ✅        | ❌      | ❌          | ❌     |
| Add / Edit / Delete Participant | ❌   | ✅        | ❌      | ❌          | ❌     |
| Approve Participant           | ❌    | ✅        | ❌      | ❌          | ❌     |
| View Seminar Schedule         | ✅    | ✅        | ✅      | ✅          | ✅     |
| View Participant List         | ❌    | ✅        | ✅(ตัวเอง)| ❌        | ❌     |
| Upload Slides                 | ❌    | ❌        | ✅      | ❌          | ❌     |
| Give Feedback                 | ❌    | ❌        | ❌      | ✅          | ❌     |
| Export Reports                | ✅    | ✅        | ❌      | ❌          | ❌     |
| Backup / System Control       | ✅    | ❌        | ❌      | ❌          | ❌     |

---


## 💻 Seminar Management System - Code Workflow with Access Level

### Legend
- 🔴 Admin / Organizer  
- 🟢 Speaker  
- 🟡 Participant  
- ⚪ Viewer  

```mermaid
flowchart TD
    Start([Start Program]) --> Home([Menu Loop])

    %% Add Seminar
    Home -->|Option 1| AddSeminar([Add Seminar])
    AddSeminar --> RoleCheckAdd{User Role?}
    RoleCheckAdd -->|Admin / Organizer| ConfirmAdd([Confirm Add Seminar])
    RoleCheckAdd -->|Speaker| DeniedSpeakerAdd([Access Denied])
    RoleCheckAdd -->|Participant| DeniedParticipantAdd([Access Denied])
    RoleCheckAdd -->|Viewer| DeniedViewerAdd([Access Denied])
    ConfirmAdd --> Home
    DeniedSpeakerAdd --> Home
    DeniedParticipantAdd --> Home
    DeniedViewerAdd --> Home

    %% Search Seminar
    Home -->|Option 2| Search([Search Seminar])
    Search --> RoleCheckSearch{User Role?}
    RoleCheckSearch -->|All Roles| ShowOption([Show All or Search Keyword])
    ShowOption -->|All| ShowAll([Show All Seminars])
    ShowOption -->|Keyword| KeywordSearch([Search Keyword])
    ShowAll --> Home
    KeywordSearch --> Home

    %% Update Seminar
    Home -->|Option 3| Update([Update Seminar])
    Update --> RoleCheckUpdate{User Role?}
    RoleCheckUpdate -->|Admin / Organizer| KeywordUpdate([Search Keyword to Update])
    RoleCheckUpdate -->|Speaker| DeniedSpeakerUpdate([Access Denied])
    RoleCheckUpdate -->|Participant| DeniedParticipantUpdate([Access Denied])
    RoleCheckUpdate -->|Viewer| DeniedViewerUpdate([Access Denied])
    KeywordUpdate --> SelectUpdate([Select Result Number])
    SelectUpdate --> EditData([Input New Seminar Data])
    EditData --> SaveUpdate([Save to temp.csv → Replace celender.csv])
    SaveUpdate --> Home
    DeniedSpeakerUpdate --> Home
    DeniedParticipantUpdate --> Home
    DeniedViewerUpdate --> Home

    %% Delete Seminar
    Home -->|Option 4| Delete([Delete Seminar])
    Delete --> RoleCheckDelete{User Role?}
    RoleCheckDelete -->|Admin / Organizer| KeywordDelete([Search Keyword to Delete])
    RoleCheckDelete -->|Speaker| DeniedSpeakerDelete([Access Denied])
    RoleCheckDelete -->|Participant| DeniedParticipantDelete([Access Denied])
    RoleCheckDelete -->|Viewer| DeniedViewerDelete([Access Denied])
    KeywordDelete --> SelectDelete([Select Result Numbers])
    SelectDelete --> BackupDelete([Backup Deleted Data])
    BackupDelete --> UpdateCSV([Save to temp.csv → Replace celender.csv])
    UpdateCSV --> Home
    DeniedSpeakerDelete --> Home
    DeniedParticipantDelete --> Home
    DeniedViewerDelete --> Home

    %% Exit
    Home -->|Option 0| Exit([Exit Program])

    %% Styling Role
    class ConfirmAdd,KeywordUpdate,SelectUpdate,EditData,SaveUpdate,KeywordDelete,SelectDelete,BackupDelete,UpdateCSV AdminOrOrganizer
    class DeniedSpeakerAdd,DeniedSpeakerUpdate,DeniedSpeakerDelete Speaker
    class DeniedParticipantAdd,DeniedParticipantUpdate,DeniedParticipantDelete Participant
    class DeniedViewerAdd,DeniedViewerUpdate,DeniedViewerDelete Viewer

    classDef AdminOrOrganizer fill:#f88,stroke:#333,stroke-width:1px,color:#000
    classDef Speaker fill:#8f8,stroke:#333,stroke-width:1px,color:#000
    classDef Participant fill:#ff8,stroke:#333,stroke-width:1px,color:#000
    classDef Viewer fill:#eee,stroke:#333,stroke-width:1px,color:#000
