#include <string.h>
#include "LegoAnim.h"
#include "LegoStorage.h"


LegoSplineFlags::LegoSplineFlags()
{
    m_useTension = FALSE;
    m_useContinuity = FALSE;
    m_useBias = FALSE;
    m_useEaseTo = FALSE;
    m_useEaseFrom = FALSE;
}

LegoResult 
LegoSplineFlags::Read(LegoStorage* p_storage)
{
    LegoResult result;
    LegoU8 bits;
    if ((result = p_storage->Read(&bits, sizeof(bits))) != SUCCESS) {
        return result;
    }
    m_useTension = bits & 0x01;
    m_useContinuity = bits & 0x02;
    m_useBias = bits & 0x04;
    m_useEaseTo = bits & 0x08;
    m_useEaseFrom = bits & 0x10;
    return SUCCESS;
}

LegoResult 
LegoSplineFlags::Write(LegoStorage* p_storage)
{
    LegoResult result;
    LegoU8 bits = 
        m_useTension
        |
        m_useContinuity << 1
        |
        m_useBias << 2
        |
        m_useEaseTo << 3
        |
        m_useEaseFrom << 4;

    if ((result = p_storage->Write(&bits, sizeof(bits))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoSplineParameters::LegoSplineParameters()
{
    m_tension = 0.0F;
    m_continuity = 0.0F;
    m_bias = 0.0F;
    m_easeTo = 0.0F;
    m_easeFrom = 0.0F;
}

LegoResult 
LegoSplineParameters::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_flags.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if (m_flags.GetUseTension()) {
        if ((result = p_storage->Read(&m_tension, sizeof(m_tension))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseContinuity()) {
        if ((result = p_storage->Read(&m_continuity, sizeof(m_continuity))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseBias()) {
        if ((result = p_storage->Read(&m_bias, sizeof(m_bias))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseEaseTo()) {
        if ((result = p_storage->Read(&m_easeTo, sizeof(m_easeTo))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseEaseFrom()) {
        if ((result = p_storage->Read(&m_easeFrom, sizeof(m_easeFrom))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoSplineParameters::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_flags.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if (m_flags.GetUseTension()) {
        if ((result = p_storage->Write(&m_tension, sizeof(m_tension))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseContinuity()) {
        if ((result = p_storage->Write(&m_continuity, sizeof(m_continuity))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseBias()) {
        if ((result = p_storage->Write(&m_bias, sizeof(m_bias))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseEaseTo()) {
        if ((result = p_storage->Write(&m_easeTo, sizeof(m_easeTo))) != SUCCESS) {
            return result;
        }
    }
    if (m_flags.GetUseEaseFrom()) {
        if ((result = p_storage->Write(&m_easeFrom, sizeof(m_easeFrom))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoAnimKey::LegoAnimKey()
{
    m_time = 0;
}

LegoResult 
LegoAnimKey::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_time, sizeof(m_time))) != SUCCESS) {
        return result;
    }
    if ((result = m_splineParameters.Read(p_storage)) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoAnimKey::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_time, sizeof(m_time))) != SUCCESS) {
        return result;
    }
    if ((result = m_splineParameters.Write(p_storage)) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoTranslationKey::LegoTranslationKey()
{
    m_x = 0.0F;
    m_y = 0.0F;
    m_z = 0.0F;
}

LegoResult 
LegoTranslationKey::Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Read(p_storage)) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Read(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Read(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Read(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoTranslationKey::Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Write(p_storage)) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Write(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Write(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Write(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoRotationKey::LegoRotationKey()
{
    m_angle = 0.0F;
    m_x = 0.0F;
    m_y = 0.0F;
    m_z = 0.0F;
}

LegoResult 
LegoRotationKey::Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_angle, sizeof(m_angle))) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Read(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Read(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Read(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoRotationKey::Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_angle, sizeof(m_angle))) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Write(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Write(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Write(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoScaleKey::LegoScaleKey()
{
    m_x = 0.0F;
    m_y = 0.0F;
    m_z = 0.0F;
}

LegoResult 
LegoScaleKey::Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Read(p_storage)) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Read(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Read(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Read(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoScaleKey::Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ)
{
    LegoResult result;
    if ((result = LegoAnimKey::Write(p_storage)) != SUCCESS) {
        return result;
    }
    if (p_useX) {
        if ((result = p_storage->Write(&m_x, sizeof(m_x))) != SUCCESS) {
            return result;
        }
    }
    if (p_useY) {
        if ((result = p_storage->Write(&m_y, sizeof(m_y))) != SUCCESS) {
            return result;
        }
    }
    if (p_useZ) {
        if ((result = p_storage->Write(&m_z, sizeof(m_z))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoMorphKey::LegoMorphKey()
{
    m_name = NULL;
}

LegoResult 
LegoMorphKey::Read(LegoStorage* p_storage)
{
    LegoResult result;
    LegoU32 length;
    if ((result = LegoAnimKey::Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&length, sizeof(length))) != SUCCESS) {
        return result;
    }
    if (m_name) {   
        delete [] m_name;
        m_name = NULL;
    }
    if (length) {
        m_name = new LegoChar[length + 1];
        if ((result = p_storage->Read(m_name, length)) != SUCCESS) {
            return result;
        }
        m_name[length] = '\0';
    }
    return SUCCESS;
}

LegoResult 
LegoMorphKey::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = LegoAnimKey::Write(p_storage)) != SUCCESS) {
        return result;
    }
    LegoU32 length = 0;
    if (m_name) {
        length = strlen(m_name);
    }
    if ((result = p_storage->Write(&length, sizeof(length))) != SUCCESS) {
        return result;
    }
    if (m_name) {
        if ((result = p_storage->Write(m_name, length)) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

void 
LegoMorphKey::SetName(const LegoChar* p_name)
{
    if (m_name) {
        delete [] m_name;
    }
    m_name = new LegoChar[strlen(p_name) + 1];
    strcpy(m_name, p_name);
}


LegoAnimTrackFlags::LegoAnimTrackFlags()
{
    m_loop = FALSE;
    m_lockX = FALSE;
    m_lockY = FALSE;
    m_lockZ = FALSE;
}

LegoResult 
LegoAnimTrackFlags::Read(LegoStorage* p_storage)
{
    LegoResult result;
    LegoU8 bits;
    if ((result = p_storage->Read(&bits, sizeof(bits))) != SUCCESS) {
        return result;
    }
    m_loop = bits & 0x01;
    m_lockX = bits & 0x02;
    m_lockY = bits & 0x04;
    m_lockZ = bits & 0x08;
    return SUCCESS;
}

LegoResult 
LegoAnimTrackFlags::Write(LegoStorage* p_storage)
{
    LegoResult result;
    LegoU8 bits = 
        m_loop
        |
        m_lockX << 1
        |
        m_lockY << 2
        |
        m_lockZ << 3;

    if ((result = p_storage->Write(&bits, sizeof(bits))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoAnimNodeData::LegoAnimNodeData()
{
    m_name = NULL;
    m_numTranslationKeys = 0;
    m_translationKeys = NULL;
    m_numRotationKeys = 0;
    m_rotationKeys = NULL;
    m_numScaleKeys = 0;
    m_scaleKeys = NULL;
    m_numMorphKeys = 0;
    m_morphKeys = NULL;
}

LegoAnimNodeData::~LegoAnimNodeData()
{
    if (m_name) {
        delete [] m_name;
    }
    if (m_translationKeys) {
        delete [] m_translationKeys;
    }
    if (m_rotationKeys) {
        delete [] m_rotationKeys;
    }
    if (m_scaleKeys) {
        delete [] m_scaleKeys;
    }
    if (m_morphKeys) {
        delete [] m_morphKeys;
    }
}

LegoResult 
LegoAnimNodeData::Read(LegoStorage* p_storage)
{
    LegoResult result;

    LegoU32 length;
    if ((result = p_storage->Read(&length, sizeof(length))) != SUCCESS) {
        return result;
    }
    if (m_name) {   
        delete [] m_name;
        m_name = NULL;
    }
    if (length) {
        m_name = new LegoChar[length + 1];
        if ((result = p_storage->Read(m_name, length)) != SUCCESS) {
            return result;
        }
        m_name[length] = '\0';
    }

    if ((result = m_pivot.Read(p_storage)) != SUCCESS) {
        return result;
    }

    LegoU32 i;

    if ((result = m_translationFlags.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_numTranslationKeys, sizeof(m_numTranslationKeys))) != SUCCESS) {
        return result;
    }
    if (m_translationKeys) {
        delete [] m_translationKeys;
        m_translationKeys = NULL;
    }
    if (m_numTranslationKeys) {
        m_translationKeys = new LegoTranslationKey[m_numTranslationKeys];
        for (i = 0; i < m_numTranslationKeys; i++) {
            if ((result = m_translationKeys[i].Read(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_rotationFlags.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_numRotationKeys, sizeof(m_numRotationKeys))) != SUCCESS) {
        return result;
    }
    if (m_rotationKeys) {
        delete [] m_rotationKeys;
        m_rotationKeys = NULL;
    }
    if (m_numRotationKeys) {
        m_rotationKeys = new LegoRotationKey[m_numRotationKeys];
        for (i = 0; i < m_numRotationKeys; i++) {
            if ((result = m_rotationKeys[i].Read(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_scaleFlags.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_numScaleKeys, sizeof(m_numScaleKeys))) != SUCCESS) {
        return result;
    }
    if (m_scaleKeys) {
        delete [] m_scaleKeys;
        m_scaleKeys = NULL;
    }
    if (m_numScaleKeys) {
        m_scaleKeys = new LegoScaleKey[m_numScaleKeys];
        for (i = 0; i < m_numScaleKeys; i++) {
            if ((result = m_scaleKeys[i].Read(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_morphFlags.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_numMorphKeys, sizeof(m_numMorphKeys))) != SUCCESS) {
        return result;
    }
    if (m_morphKeys) {
        delete [] m_morphKeys;
        m_morphKeys = NULL;
    }
    if (m_numMorphKeys) {
        m_morphKeys = new LegoMorphKey[m_numMorphKeys];
        for (i = 0; i < m_numMorphKeys; i++) {
            if ((result = m_morphKeys[i].Read(p_storage)) != SUCCESS) {
                return result;
            }
        }
    }

    return SUCCESS;
}

LegoResult 
LegoAnimNodeData::Write(LegoStorage* p_storage)
{
    LegoResult result;

    LegoU32 length = 0;
    if (m_name) {
        length = strlen(m_name);
    }
    if ((result = p_storage->Write(&length, sizeof(length))) != SUCCESS) {
        return result;
    }
    if (m_name) {
        if ((result = p_storage->Write(m_name, length)) != SUCCESS) {
            return result;
        }
    }

    if ((result = m_pivot.Write(p_storage)) != SUCCESS) {
        return result;
    }

    LegoU32 i;

    if ((result = m_translationFlags.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_numTranslationKeys, sizeof(m_numTranslationKeys))) != SUCCESS) {
        return result;
    }
    if (m_numTranslationKeys) {
        for (i = 0; i < m_numTranslationKeys; i++) {
            if ((result = m_translationKeys[i].Write(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_rotationFlags.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_numRotationKeys, sizeof(m_numRotationKeys))) != SUCCESS) {
        return result;
    }
    if (m_numRotationKeys) {
        for (i = 0; i < m_numRotationKeys; i++) {
            if ((result = m_rotationKeys[i].Write(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_scaleFlags.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_numScaleKeys, sizeof(m_numScaleKeys))) != SUCCESS) {
        return result;
    }
    if (m_numScaleKeys) {
        for (i = 0; i < m_numScaleKeys; i++) {
            if ((result = m_scaleKeys[i].Write(p_storage, !m_translationFlags.GetLockX(), !m_translationFlags.GetLockY(), !m_translationFlags.GetLockZ())) != SUCCESS) {
                return result;
            }
        }
    }

    if ((result = m_morphFlags.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_numMorphKeys, sizeof(m_numMorphKeys))) != SUCCESS) {
        return result;
    }
    if (m_numMorphKeys) {
        for (i = 0; i < m_numMorphKeys; i++) {
            if ((result = m_morphKeys[i].Write(p_storage)) != SUCCESS) {
                return result;
            }
        }
    }

    return SUCCESS;
}

void
LegoAnimNodeData::SetName(const LegoChar* p_name)
{
    if (m_name) {
        delete [] m_name;
    }
    m_name = new LegoChar[strlen(p_name) + 1];
    strcpy(m_name, p_name);
}

void
LegoAnimNodeData::GetTranslation(LegoTime p_time, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z)
{
    LegoU32 i, n;
    n = FindKeys(p_time, m_numTranslationKeys, m_translationKeys, sizeof(LegoTranslationKey), i);
    switch (n) {
    case 0:
        p_x = 0.0F;
        p_y = 0.0F;
        p_z = 0.0F;
        break;
    case 1:
        p_x = m_translationKeys[i].GetX();
        p_y = m_translationKeys[i].GetY();
        p_z = m_translationKeys[i].GetZ();
        break;
    case 2:
        p_x = Interpolate(p_time, m_translationKeys[i], m_translationKeys[i].GetX(), m_translationKeys[i + 1], m_translationKeys[i + 1].GetX());
        p_y = Interpolate(p_time, m_translationKeys[i], m_translationKeys[i].GetY(), m_translationKeys[i + 1], m_translationKeys[i + 1].GetY());
        p_z = Interpolate(p_time, m_translationKeys[i], m_translationKeys[i].GetZ(), m_translationKeys[i + 1], m_translationKeys[i + 1].GetZ());
        break;
    }
}

void
LegoAnimNodeData::GetRotation(LegoTime p_time, LegoFloat& p_angle, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z)
{
    LegoU32 i, n;
    n = FindKeys(p_time, m_numRotationKeys, m_rotationKeys, sizeof(LegoRotationKey), i);
    switch (n) {
    case 0:
        p_angle = 0.0F;
        p_x = 1.0F;
        p_y = 0.0F;
        p_z = 0.0F;
        break;
    case 1:
        p_angle = m_rotationKeys[i].GetAngle();
        p_x = m_rotationKeys[i].GetX();
        p_y = m_rotationKeys[i].GetY();
        p_z = m_rotationKeys[i].GetZ();
        break;
    case 2:
        p_angle = Interpolate(p_time, m_rotationKeys[i], m_rotationKeys[i].GetAngle(), m_rotationKeys[i + 1], m_rotationKeys[i + 1].GetAngle());
        p_x = Interpolate(p_time, m_rotationKeys[i], m_rotationKeys[i].GetX(), m_rotationKeys[i + 1], m_rotationKeys[i + 1].GetX());
        p_y = Interpolate(p_time, m_rotationKeys[i], m_rotationKeys[i].GetY(), m_rotationKeys[i + 1], m_rotationKeys[i + 1].GetY());
        p_z = Interpolate(p_time, m_rotationKeys[i], m_rotationKeys[i].GetZ(), m_rotationKeys[i + 1], m_rotationKeys[i + 1].GetZ());
        break;
    }
}

void
LegoAnimNodeData::GetScale(LegoTime p_time, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z)
{
    LegoU32 i, n;
    n = FindKeys(p_time, m_numScaleKeys, m_scaleKeys, sizeof(LegoScaleKey), i);
    switch (n) {
    case 0:
        p_x = 1.0F;
        p_y = 1.0F;
        p_z = 1.0F;
        break;
    case 1:
        p_x = m_scaleKeys[i].GetX();
        p_y = m_scaleKeys[i].GetY();
        p_z = m_scaleKeys[i].GetZ();
        break;
    case 2:
        p_x = Interpolate(p_time, m_scaleKeys[i], m_scaleKeys[i].GetX(), m_scaleKeys[i + 1], m_scaleKeys[i + 1].GetX());
        p_y = Interpolate(p_time, m_scaleKeys[i], m_scaleKeys[i].GetY(), m_scaleKeys[i + 1], m_scaleKeys[i + 1].GetY());
        p_z = Interpolate(p_time, m_scaleKeys[i], m_scaleKeys[i].GetZ(), m_scaleKeys[i + 1], m_scaleKeys[i + 1].GetZ());
        break;
    }
}

LegoU32
LegoAnimNodeData::FindKeys(LegoTime p_time, LegoU32 p_numKeys, LegoAnimKey* p_keys, LegoU32 p_size, LegoU32& p_index)
{
    LegoU32 numKeys;
    if (p_numKeys == 0) {
        numKeys = 0;
    }
    else if (p_time < GetKey(0, p_keys, p_size).GetTime()) {
        p_index = 0;
        numKeys = 1;
    }
    else if (p_time > GetKey(p_numKeys - 1, p_keys, p_size).GetTime()) {
        p_index = p_numKeys - 1;
        numKeys = 1;
    }
    else {
        for (p_index = 0; p_index < p_numKeys - 1 && p_time >= GetKey(p_index + 1, p_keys, p_size).GetTime(); p_index++);
        if (p_time == GetKey(p_index, p_keys, p_size).GetTime()) {
            numKeys = 1;
        }
        else if (p_index < p_numKeys - 1) {
            numKeys = 2;
        }
        else {
            numKeys = 0;
        }
    }
    return numKeys;
}

LegoFloat
LegoAnimNodeData::Interpolate(LegoTime p_time, LegoAnimKey& p_key1, LegoFloat p_value1, LegoAnimKey& p_key2, LegoFloat p_value2)
{
    return p_value1 + (p_value2 - p_value1) * (p_time - p_key1.GetTime()) / (p_key2.GetTime() - p_key1.GetTime());
}

LegoAnimKey&
LegoAnimNodeData::GetKey(LegoU32 p_i, LegoAnimKey* p_keys, LegoU32 p_size)
{
    return *((LegoAnimKey*) (((LegoU8*) p_keys) + (p_i * p_size)));
}

#ifdef _DEBUG
void 
LegoAnimNodeData::Dump(FILE* p_file)
{
    LegoChar* name = m_name ? m_name : "";
    fprintf(p_file, "%s", name);
}
#endif

LegoAnim::LegoAnim()
{
    m_duration = 0;
}

void 
LegoAnim::CalculateDuration()
{
    m_duration = 0;
    CalculateDuration(m_root);
}

void 
LegoAnim::CalculateDuration(LegoTreeNode* p_node)
{
    LegoAnimNodeData* data = (LegoAnimNodeData*) p_node->GetData();
    if (data->GetNumTranslationKeys() && data->GetTranslationKey(data->GetNumTranslationKeys() - 1).GetTime() > m_duration) {
        m_duration = data->GetTranslationKey(data->GetNumTranslationKeys() - 1).GetTime();
    }
    if (data->GetNumRotationKeys() && data->GetRotationKey(data->GetNumRotationKeys() - 1).GetTime() > m_duration) {
        m_duration = data->GetRotationKey(data->GetNumRotationKeys() - 1).GetTime();
    }
    if (data->GetNumScaleKeys() && data->GetScaleKey(data->GetNumScaleKeys() - 1).GetTime() > m_duration) {
        m_duration = data->GetScaleKey(data->GetNumScaleKeys() - 1).GetTime();
    }
    if (data->GetNumMorphKeys() && data->GetMorphKey(data->GetNumMorphKeys() - 1).GetTime() > m_duration) {
        m_duration = data->GetMorphKey(data->GetNumMorphKeys() - 1).GetTime();
    }
    for (LegoU32 i = 0; i < p_node->GetNumChildren(); i++) {
        CalculateDuration(p_node->GetChild(i));
    }
}

LegoResult 
LegoAnim::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_duration, sizeof(m_duration))) != SUCCESS) {
        return result;
    }
    return LegoTree::Read(p_storage);
}

LegoResult 
LegoAnim::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_duration, sizeof(m_duration))) != SUCCESS) {
        return result;
    }
    return LegoTree::Write(p_storage);
}


