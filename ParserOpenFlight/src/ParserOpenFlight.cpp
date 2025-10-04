#include "../include/ParserOpenFlight.hpp"


void ParserOpenFlight::parse_records(std::ifstream& file, int depth)
{
    while (true) {
        std::streampos pos = file.tellg();
        Record rec{};
        if (!file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
            break;
        }

        rec.opcode = swap16(rec.opcode);
        rec.length = swap16(rec.length);

        if (rec.length < sizeof(rec)) {
            break;
        }

        auto print_indent = [&](int depth) {
            return std::string(depth * 2, ' ');
        };

        switch (rec.opcode) {
        case PUSH_LEVEL: {
            PushLevelRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            std::cout << print_indent(depth) << "[Push Level]" << std::endl;
            parse_records(file, depth + 1);
            break;
        }

        case POP_LEVEL: {
            PopLevelRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            std::cout << print_indent(depth) << "[Pop Level]" << std::endl;
            return;
        }

        case PUSH_SUBFACE: {
            PushSubfaceRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            std::cout << print_indent(depth) << "[Push Subface]" << std::endl;
            break;
        }

        case POP_SUBFACE: {
            PopSubfaceRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            std::cout << print_indent(depth) << "[Pop Subface]" << std::endl;
            break;
        }

        case PUSH_EXTENSION: {
            PushExtensionRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.vertex_ref_index = swap16(rec.vertex_ref_index);

            std::cout << print_indent(depth) << "[Push Extension] VertexRefIndex = " << rec.vertex_ref_index << std::endl;
            break;
        }

        case POP_EXTENSION: {
            PopExtensionRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.vertex_ref_index = swap16(rec.vertex_ref_index);

            std::cout << print_indent(depth) << "[Pop Extension] VertexRefIndex = " << rec.vertex_ref_index << std::endl;
            break;
        }

        case PUSH_ATTRIBUTE: {
            PushAttributeRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.vertex_ref_index = swap32(rec.vertex_ref_index);

            std::cout << print_indent(depth) << "[Push Attribute] VertexRefIndex = " << rec.vertex_ref_index << std::endl;
            break;
        }

        case POP_ATTRIBUTE: {
            PopAttributeRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);

            std::cout << print_indent(depth) << "[Pop Attribute]" << std::endl;
            break;
        }

        case INSTANCE_REFERENCE: {
            InstanceReferenceRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.definition_number = swap32(rec.definition_number);

            std::cout << print_indent(depth) << "[Instance Reference] ID = " << rec.definition_number << std::endl;
            break;
        }

        case INSTANCE_DEFINITION: {
            InstanceDefinitionRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.definition_number = swap32(rec.definition_number);

            std::cout << print_indent(depth) << "[Instance Definition] ID=" << rec.definition_number << std::endl;
            break;
        }

        case HEADER:{
            HeaderRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);
            rec.format_revision = swap32(rec.format_revision);

            std::string version;
            switch (rec.format_revision) {
            case 1110: version = "Flight v11"; break;
            case 1200: version = "Flight v12"; break;
            case 1400: version = "OpenFlight v14.0 / v14.1"; break;
            case 1420: version = "OpenFlight v14.2"; break;
            case 1510: version = "OpenFlight v15.1"; break;
            case 1540: version = "OpenFlight v15.4"; break;
            case 1550: version = "OpenFlight v15.5"; break;
            case 1560: version = "OpenFlight v15.6"; break;
            case 1570: version = "OpenFlight v15.7"; break;
            case 1580: version = "OpenFlight v15.8"; break;
            case 1600: version = "OpenFlight v16.0"; break;
            case 1610: version = "OpenFlight v16.1"; break;
            case 1620: version = "OpenFlight v16.2"; break;
            case 1630: version = "OpenFlight v16.3"; break;
            case 1640: version = "OpenFlight v16.4"; break;
            default:   version = "Unknown"; break;
            }

            std::cout << print_indent(depth)
                << "[Header] '" << rec.id << "'"
                << " | Format Revision: " << rec.format_revision
                << " (" << version << ")" << std::endl;
            break;
        }

        case GROUP: {
            GroupRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);

            std::cout << print_indent(depth)
                << "[Group] '" << rec.id << "'" << std::endl;
            break;
        }

        case OBJECT: {
            ObjectRecord rec{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

            rec.opcode = swap16(rec.opcode);
            rec.length = swap16(rec.length);

            std::cout << print_indent(depth) << "[Object] '" << rec.id << "'" << std::endl;
            break;
        }

        case FACE: {
            FaceRecord face{};
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&face), sizeof(face));

            face.opcode = swap16(face.opcode);
            face.length = swap16(face.length);
            face.ir_color_code = swap32(face.ir_color_code);
            face.material_index = swap16(face.material_index);

            std::cout << print_indent(depth)
                << "[Polygon] '" << face.id << "'"
                << " | Color name index = " << face.ir_color_code
                << " | Material index = " << face.material_index << std::dec
                << std::endl;
            break;
        }

        case COLOR_PALETTE:
            std::cout << print_indent(depth) << "[Color palette]" << std::endl;
            break;

        case MATERIAL_PALETTE:
            std::cout << print_indent(depth) << "[Material palette]" << std::endl;
            break;

        case LIGHT_SOURCE_PALETTE:
            std::cout << print_indent(depth) << "[Light source palette]" << std::endl;
            break;

        case EYEPOINT_AND_TRACKPLANE_PALETTE:
            std::cout << print_indent(depth) << "[Eyepoint and trackplane palette]" << std::endl;
            break;

        case VERTEX_PALETTE:
            std::cout << print_indent(depth) << "[Vertex Palette]" << std::endl;
            break;

        case VERTEX_CN:
            std::cout << print_indent(depth) << "[Vertex cn]" << std::endl;
            break;

        case LONG_ID:
            std::cout << print_indent(depth) << "[Long id]" << std::endl;
            break;

        case VERTEX_LIST:
            std::cout << print_indent(depth) << "[Vertex list]" << std::endl;
            break;

        default:
            std::cout << print_indent(depth) << "[Unknown opcode " << rec.opcode << "] (len=" << rec.length << ")" << std::endl;
            break;
        }

        file.seekg(pos + static_cast<std::streamoff>(rec.length));
    }
}